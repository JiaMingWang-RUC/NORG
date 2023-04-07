#include "impurity.h"

Impurity::Impurity(const MyMpi &mm_i, const Prmtr &prmtr_i, const Bath &bth_i, const Str& file)
    : mm(mm_i), p(prmtr_i), bth(bth_i), nb(p.nbath), ni(p.norbs), ns(p.norbit), pos_imp(p.norbs), h0(p.norbit, p.norbit, 0.), imp_lvl(p.norbs)
{
    // if (!file.empty()) read(file);
    for_Int(i, 0, ni) imp_lvl[i] = p.eimp[i] - p.mu;
    set_factor();
    impH = std::make_pair(h0, set_interaction());
}

Impurity::Impurity(const MyMpi &mm_i, const Prmtr &prmtr_i, const Bath &bth_i, const VecInt or_deg)
    : mm(mm_i), p(prmtr_i), bth(bth_i), nb(p.nbath), ni(p.norbs), ns(p.norbit), pos_imp(p.norbs), h0(p.norbit, p.norbit, 0.), imp_lvl(p.norbs, 0.)
{
    // if (!file.empty()) read(file);
    VecInt ordeg(concat(or_deg,or_deg).mat(2, p.nband).tr().vec());
    // if(mm) WRN(NAV(ordeg));
    VecReal deg_lvl(MAX(ordeg), 0.);
    for_Int(i, 0, ni) deg_lvl[ordeg[i] - 1] += p.eimp[i] - p.mu;
    for_Int(i, 0, MAX(ordeg)) {
        Int cnt(0);
        for_Int(j, 0, ni) if(i == ordeg[j] - 1) cnt++;
        deg_lvl[i] = deg_lvl[i] / Real(cnt);
    }
    for_Int(i, 0, ni) imp_lvl[i] = deg_lvl[ordeg[i] - 1];
    set_factor();

    impH = std::make_pair(h0, set_interaction());
}

using namespace std;

// rely on imp model's frame
void Impurity::find_g0(Green &g0) const {

    MatCmplx Z(ns, ns);
    for_Int(n, 0, g0.nomgs) {
        Z = g0.z(n);
        MatCmplx g0_z = matinvlu(Z - cmplx(h0));
        for_Int(i, 0, p.nband) {
            g0[n][i][i] = g0_z[pos_imp[2 * i]][pos_imp[2 * i]];
        }
    }
}

// rely on imp model's frame
void Impurity::find_all_g0(Green &g0) const {

    MatCmplx Z(ns, ns);
    for_Int(n, 0, g0.nomgs) {
        Z = g0.z(n);
        MatCmplx g0_z = matinvlu(Z - cmplx(h0));
        for_Int(i, 0, p.norbit) {
            g0[n][i][i] = g0_z[i][i];
        }
    }
}

//rely on imp model's frame
void Impurity::find_hb(Green &hb) const {
    for_Int(i,0,p.nband){
        const Int nb_i = p.nI2B[2*i];
        for_Int(n,0,hb.nomgs){
            const VecCmplx Z(nb_i, hb.z(n));
            VecCmplx S = INV(Z - cmplx(bth.vec_ose[i]));
            VecCmplx V = cmplx(bth.vec_hop[i]);
            hb[n][i][i] = -SUM(V * S * V.co());
            //hb[n][i][i] = DOT(cmplx(bth.vec_hop[i]), S * cmplx(bth.vec_hop[i]));
        }
    }
}

MatReal Impurity::find_hop_for_test() const
{
    VecReal hop({ -0.312546, 0.159346, -0.0619612, -0.312546, 0.159346 });
    VecReal ose({ -0.474855,0.0667285, 0,           0.474855, -0.0667285 });
    MatReal h0(0, 0, 0.);
    for_Int(i, 0, p.nband) {
        const Int nb_i = p.nI2B[i * 2];
        MatReal h0_i(1 + nb_i, 1 + nb_i, 0.);
        for_Int(j, 0, nb_i) {
            h0_i[0][j + 1] = hop[j];
            h0_i[j + 1][0] = hop[j];
            h0_i[j + 1][j + 1] = ose[j];
        }
        h0_i.reset(direct_sum(h0_i, h0_i));
        h0.reset(direct_sum(h0, h0_i));
    }
    return h0;
}

void Impurity::update() {
    set_factor();
    impH  = std::make_pair(h0,set_interaction());
}

// ! not finished.
// void Impurity::update(VecInt or_deg) {
//     for_Int()

//     set_factor();
// }

void Impurity::write_H0info(const Bath &b, Int ndeg) const {
    OFS ofs;    ofs.open("h0.txt");
    using namespace std;
    if(ndeg > 0) for_Int(i, 0, ndeg)	{
        ofs << "The impurity for "<< i+1 << "-th degeneracy: " << "nmin: " << b.info[i][0] << " err: " << b.info[i][1] << " err_crv: " << b.info[i][2] << " err_reg: " << b.info[i][3] << " norm: " << b.info[i][4]<< "  " << endl;
    }
    else for_Int(i, 0, p.nband) {
        ofs << "The impurity for "<< i+1 << "-th band: " << "nmin: " << b.info[i][0] << " err: " << b.info[i][1] << " err_crv: " << b.info[i][2] << " err_reg: " << b.info[i][3] << " norm: " << b.info[i][4]<< "  " << endl;
    }
    for_Int(i, 0, p.nband)	{
        ofs << i+1 << "-th band: " << endl;
        Int begin(i*2 * (p.nI2B[i*2] + 1)), end((i*2 + 1) * (p.nI2B[i*2] + 1));
        ofs << iofmt() << h0.truncate(begin, begin, end, end) << endl;
    }
}

//---------------------------------------------Private function---------------------------------------------


void Impurity::set_factor() {
    // set hyb part and bath part
    h0 = bth.find_hop();
    
    // // h0 = find_hop_for_test();
    // set imp part
    MatReal h0loc(ni,ni,0.);
    for_Int(i, 0, ni) h0loc[i][i] = imp_lvl[i];
    
    // find i_th imp in which site
    Int site = 0;
    for_Int(i, 0, ni) {
        pos_imp[i] = site;
        site += p.nI2B[i] + 1;
    }

    // set h0loc
    for_Int(i, 0, ni) {
        for_Int(j, 0, ni) {
            h0[pos_imp[i]][pos_imp[j]] = h0loc[i][j];
        }
    }
}

// four-fermion operator terms for C^+_i C^+_j C_k C_l; 
// C^+_i C^+_j C_k C_l h_inter from [i][l][j][k] to [alpha][eta][beta][gamma]
VecReal Impurity::set_interaction() {
    Int n = p.norbit;
    VecReal interaction(std::pow(n, 4), 0.);
    // Mat<MatReal> imp_interact(p.norbs, p.norbs, MatReal(p.norbs, p.norbs, 0.));
    MatReal imp_dd_interact(p.norbs, p.norbs,  0.);
/*
    for_Int(N_i, 0, p.norbs){
        for_Int(N_j, N_i, p.norbs) if(N_i != N_j){
            if ((N_i % 2) == (N_j % 2)) { // same spin orientation
                imp_interact[N_i][N_j][N_j][N_i] = p.Uprm - p.jz;
            } else {
                if (N_i / 2 == N_j / 2)  imp_interact[N_i][N_j][N_j][N_i] = p.U;
                else imp_interact[N_i][N_j][N_j][N_i] = p.Uprm;
            }

            if (mm) {
                Str n_i = to_string(N_i / 2) + Str(N_i % 2 == 0 ? "↑" : "↓");
                Str n_j = to_string(N_j / 2) + Str(N_j % 2 == 0 ? "↑" : "↓");
                Real value = imp_interact[N_i][N_j][N_j][N_i];
                if(value != 0) WRN(NAV3(n_i, n_j, value));
            }
            interaction[SUM_0toX(p.nO2sets, N_i) * std::pow(n, 3) + SUM_0toX(p.nO2sets, N_j) * std::pow(n, 2) + SUM_0toX(p.nO2sets, N_j) * std::pow(n, 1) + SUM_0toX(p.nO2sets, N_i)] = imp_interact[N_i][N_j][N_j][N_i];
        }
    }
*/
/* 
    for_Int(b1, 0, p.nband) {// NO double counting term for impurity
        imp_dd_interact[2 * b1][2 * b1 + 1] = p.U;
        for_Int(b2, b1, p.nband) if (b1 != b2) { // same spin orientation
            imp_dd_interact[2 * b1][2 * b2] = p.Uprm - p.jz;
            imp_dd_interact[2 * b1 + 1][2 * b2 + 1] = p.Uprm - p.jz;
        }
        for_Int(b2, 0, p.nband) if (b1 != b2) {
            imp_dd_interact[2 * b1][2 * b2 + 1] = p.Uprm;
        }
    }
*/
    for_Int(b1, 0, p.nband) {// with double counting term for impurity, so we need to divide by 2
        imp_dd_interact[2 * b1][2 * b1 + 1] = p.U/2.0;
        imp_dd_interact[2 * b1 + 1][2 * b1] = p.U/2.0;
        for_Int(b2, 0, p.nband) if (b1 != b2) { // same spin orientation
            imp_dd_interact[2 * b1][2 * b2] = (p.Uprm - p.jz)/2.0;
            imp_dd_interact[2 * b1 + 1][2 * b2 + 1] = (p.Uprm - p.jz)/2.0;
        }
        for_Int(b2, 0, p.nband) if (b1 != b2) {
            imp_dd_interact[2 * b1][2 * b2 + 1] = p.Uprm/2.0;
            imp_dd_interact[2 * b1 + 1][2 * b2] = p.Uprm/2.0;
        }
    }
    
    if(mm) WRN(NAV(imp_dd_interact));
    for_Int(N_i, 0, p.norbs)for_Int(N_j, 0, p.norbs) {
        if (imp_dd_interact[N_i][N_j] != 0)
            interaction[SUM_0toX(p.nO2sets, N_i) * std::pow(n, 3) + SUM_0toX(p.nO2sets, N_j) * std::pow(n, 2) + SUM_0toX(p.nO2sets, N_j) * std::pow(n, 1) + SUM_0toX(p.nO2sets, N_i)] = imp_dd_interact[N_i][N_j];

    }
    // if (mm) WRN(NAV5(p.U, p.Uprm ,p.nO2sets, interaction.size(), SUM(interaction[0][0])));
    return interaction;
}