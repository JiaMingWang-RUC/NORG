/*
coded by Jia-Ming Wang (jmw@ruc.edu.cn, RUC, China) date 2023.03.03
*/

// adaptive natural sampling configuration interaction

#include "asnci.h"

using namespace std;


Asnci::Asnci(const NORG& norg, Idx trncat_size, const Int mode):
    dim(trncat_size), mm(norg.mm), p(norg.p), hop_h(norg.scsp.hopint), mayhop(find_mayhop()),
    nosp(norg.scsp), groundE(norg.groune_lst)
{
    // inital = git_nci(norg);
    trncat = truncation(git_nci(norg));
}

NORG Asnci::get_norg(Tab table, Int mode) {
    NORG norg(mm, p, table);
    norg.up_date_h0_to_solve(hop_h, mode);
    return norg;    
}

//------------------------------------------------------------------ private ------------------------------------------------------------------

VEC<Int> Asnci::find_mayhop() {
    VEC<Int>    mayhop_i;
    if(hop_h.size() == 0) ERR("hop_h.size() = 0");
    for_Int(i, 0, hop_h.size())  if(ABS(hop_h.vec()[i]) > 1e-6) mayhop_i.push_back(i);
    mayhop_i.shrink_to_fit();
    return move(mayhop_i);
}

Nci Asnci::git_nci(const NORG& norg) {
    Nci         natural_cfg;
    VEC<UInt*>& cfigs(natural_cfg.first);
    VEC<Real>&  ranks(natural_cfg.second);

    VecIdx groundstate_idx(nosp.dim);
    for_Idx(i, 0, nosp.dim) groundstate_idx[i]=i;
    VecReal grndste_norm = SQR(norg.final_ground_state);
    slctsort(grndste_norm, groundstate_idx);
    for_Int(i, 0, Int(dim/Int(mayhop.size()/2))){
        // if(grndste_norm[i] > 1e-5){
        {
            Idx ci_idx = groundstate_idx[i];
            StateStatistics cig(ci_idx, nosp.wherein_NocSpace(ci_idx), nosp);
            cfigs.push_back(cig.cfg2nums());
            ranks.push_back(grndste_norm[i]);
        }
    }
    expand(natural_cfg); cfigs.shrink_to_fit(); ranks.shrink_to_fit();
    return natural_cfg;
}


void Asnci::expand(Nci& natural_cfgs) {
    VEC<UInt*>& cfigs(natural_cfgs.first);
    VEC<Real>&  ranks(natural_cfgs.second);

    Vec<Str> cfigs_core;
    for_Idx(i, 0, cfigs.size()){
        Str cfg_str;
        for_Int(j, 0, p.norbs) cfg_str += to_binary_string(cfigs[i][j/2]);
        cfigs_core[i] = cfg_str;
    }
    for_Idx(i, 0, cfigs_core.size()){
        for(const auto j : mayhop) if(judge(cfigs_core[i], j)) {
            Str new_cfig(change_cfg_str(cfigs_core[i], j));
            UInt nbath_orb(0), nums[p.nband];
            Real rank;
            for_Int(k, 0, p.nband) {
                Str alpha;
                for_Int(l, SUM_0toX(p.nI2B, k * 2), SUM_0toX(p.nI2B, (k+1) * 2)) alpha += cfigs_core[i][l];
                const UInt num {std::stoul(alpha, nullptr, 2)};
                nums[i] = num;
                rank = cfi2rank(alpha, cfigs_core);
            }
            cfigs.push_back(nums);
            ranks.push_back(rank);
        }
    }
}

Nci Asnci::truncation(Nci& inital) {

    VEC<UInt*>& cfigs(inital.first);
    VEC<Real>&  rank(inital.second);

    slctsort(rank, cfigs);
    for_Idx(cunt, 0, dim){// add the map
        cfigs[cunt]  = inital.first[cunt];
        rank[cunt]  = inital.second[cunt];
        cfig_idx.insert(pair<UInt*, Int>(cfigs[cunt], cunt));
    }
    return pair(cfigs, rank);
}

Tab Asnci::find_table(Str inter_type)
{
	clock_t t_find_hmlt_table;
	t_find_hmlt_table = clock(); // TIME_BGN("find_hmlt_table" + NAV(mm.id()), t_find_hmlt_table);
	VecPartition row_H(mm.np(), mm.id(), dim);
	Tab h_idxs(3);
	MatInt mat_hop_pos(nosp.hopint.nrows(),nosp.hopint.ncols());
	for_Int(i, 0, mat_hop_pos.nrows()) for_Int(j, 0, mat_hop_pos.ncols()) mat_hop_pos[i][j] = i * mat_hop_pos.ncols() + j;
	Int h_hbd_idx(mat_hop_pos.size()	+ 1);
	Int h_orb_ud_idx(mat_hop_pos.size() + 2);
	Int h_orb_uu_idx(mat_hop_pos.size() + 3);
	Int h_orb_dd_idx(mat_hop_pos.size() + 4);

    return h_idxs;
}

Real Asnci::hamilton_value(const Str alpha, const Str beta_i = Str()) {
    Real value(0.), u(p.hubbU), j = (p.jz);
    Idx nimp(p.norbs), nband(p.nband), norb(p.norbit);
    if(beta_i.length() == 0 || (alpha == beta_i)) {
        Vec<Char> a(alpha.length()); for_Int(i, 0, a.size()) a[i] = alpha[i];
        Vec<Char> impcfig = a.mat(nband, p.nI2B[0] + 1).tr()[0];
        value += hop_h.trace();

        // add the U.
        for_Int(i, 0, nband) if (impcfig[2 * i] == '1' && impcfig[2 * i + 1] == '1') value += u;

        // add the up-down term.
        for_Int(i, 0, nband)
            for_Int(j, 0, nband) if (i != j && impcfig[2 * i] == '1' && impcfig[2 * j + 1] == '1')
                value += u - 2 * j;

        // add the up-up term.
        for_Int(i, 0, nband)
            for_Int(j, 0, nband) if (i != j && impcfig[2 * i] == '1' && impcfig[2 * j] == '1')
                value += u - 3 * j;

        // add the down-down term.
        for_Int(i, 0, nband)
            for_Int(j, 0, nband) if (i != j && impcfig[2 * i + 1] == '1' && impcfig[2 * j + 1] == '1')
                value += u - 3 * j;

        return value;
    }
    else {
        Vec<Char> a(alpha.length()), b(beta_i.length());
        for_Int(i, 0, a.size()) {a[i] = alpha[i]; b[i] = beta_i[i];}
        Vec<Char> a_cfig = a.mat(nband, p.nI2B[0] + 1).vec(), b_cfig = b.mat(nband, p.nI2B[0] + 1).vec();
        Int crt(-1), ann(-1);
        for_Int(i, 0, norb)
            if(a_cfig[i] != b_cfig[i]) {
                if(b_cfig[i] == '1')    ann = i;
                else if(b_cfig[i] == '0')  crt = i;
                else (ERR("some thing wrong in here!"));
            }
        if(crt >= 0 && ann >= 0) value += crt > ann ? hop_h[crt][ann] : - hop_h[crt][ann];
        else (ERR("some thing wrong in here!"));
        return value;
    }
}