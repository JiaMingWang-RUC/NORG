# NORG
The version of NORG for ZEN

Version: v1.0.01 @ 2023.03.14
    finished: the NC space construct.
    doing   : the NC space Hop;{find_h_idx(const Asnci& nc)}.
    tinking : how to get the projection form ground space in (n+-1) space. 

Version: v1.0.02 @ 2023.03.15
    finished: finish nc.find_h_idx(); fix the bug for the hamilton_value; fix the cfg2nums() function.
    doing   : Need to Projection form ground space in (n+-1) space. 
    tinking : check the code has no bug; check the Nci structure has no problem.

Version: v1.0.03 @ 2023.03.16
    finished: checked the code has no bug; find these bug and pass though the compiler.
    doing   : Need to Projection form ground space in (n+-1) space. 
    tinking : need to change the Nci structure, since the compiler's warning.

Version: v1.0.04 @ 2023.03.16
    finished: resit the Nci's structure, so no compiler's warning now.
    next do : Need to Projection form ground space in (n+-1) space. 
    tinking : is it fine not to build the H in (n \pm 1) subspace?

Version: v1.0.05 @ 2023.03.16
    finished: finished Projection form ground space in (n+-1) space. And make some cleaning.
    next do : Let CrrltFun support Asnci.
    tinking : Is it fine Operator construct nor use scsp's info, and if it's fine not to check the nppso?

Version: v1.0.06 @ 2023.03.16
    finished: CrrltFun support Asnci; Cut the Operator's not need functions; NOW we can test if the ASNCI can calc the green.
    next do : testing in 3-band.
    tinking : check "ex-pos" that the idx and position may not the same, since the ex-pos can't be '0'? Can single-particle excited states be generated by the rank formula?

Version: v1.0.07 @ 2023.03.17
    finished: The code can running fine when only use the NORG.
    next do : Debuging...
    tinking : What's the Rank equation comes from?

Version: v1.0.08 @ 2023.03.20
    finished: Check to find the ground state Max coefficient; double check the "cfig to arry" and "arry to cfig" function.
    next do : Check the "expand(natural_cfg)" function.
    tinking : What's the Rank equation comes from?

Version: v1.0.09 @ 2023.03.21
    finished: expand(natural_cfg) finised, but the hamilton_value still has some problem didn't fixed!
    next do : using the deflection to fix the Sgm.
    tinking : What's the Rank equation comes from? How do I converge the new space's ground state to the new n+/n- subspace?

Version: v1.0.10 @ 2023.03.21
    finished: using the deflection to fix the Sgm. (may be failed)
    next do : need to find the ground state in new space.
    tinking : What's the Rank equation comes from? How do I converge the new space's ground state to the new n+/n- subspace?

Version: v1.0.11 @ 2023.03.23
    finished: git_nci_no_rank(const VecReal& ground_state, const Int ex_pos).
    next do : test this function.
    tinking : Rank equation was writting some thing wrong? why it will calc the minus number?

Version: v1.0.12 @ 2023.03.28
    finished: change the state function, use vecbool to express; add the H to save the final coefficient.
    next do : Now face the problem with the calc Green. (Hold}
    tinking : Rank equation was writting some thing wrong? why it will calc the minus number? (Hold}

Version: v1.0.13 @ 2023.03.28
    finished: fix some print out problem.
    next do : (same as prev)
    tinking : (same as prev)

Version: v1.0.14 @ 2023.03.30
    finished: add the rotation for tensor H index. (Finished the find_fullH_idx() function.)
    next do : let prgramm test find_fullH_idx() in three band.
    tinking : Thinking about the possibility of the any mistake.

Version: v1.0.15 @ 2023.04.01
    finished: Fix the code to suit the new impurity data structure(Impdata). And the code can running fine with no bug.
    next do : 1.Cross-validation in three band. 2.add in the Green calc class new 
              (project_uplwer_parical_space(const VecReal &initial_vector, const Int crtann, const Int norg_set, const Int orbit_pos_in_div))
    tinking : <!--! Should rethink about the Asnci class since we choose rotate the whole H. -->

Version: v1.0.16 @ 2023.04.02
    finished: Fixed the set_row_primeter_byimpH() function; Add the oper_value Member variable.
    next do : 1.Cross-validation in three band. 2.add in the Green calc function.
    tinking : krylov_space_size so huge what's the problem?  <!--! A:The H matirx may illed -->

Version: v1.0.17 @ 2023.04.03
    finished: Find the bug to fix problem, "the krylov_space_size so huge". Now the energy_err can decrease constantly.
    next do : 1.add in the Green calc function.
    tinking : How to realize teh Green calc function? <!--! A:Using the for formula straight-->

Version: v1.0.18 @ 2023.04.04
    finished: fix the H matrix n_sC^+_iC_j term.
    next do : 1.add in the Green calc function.
    tinking : Only consider the n_s in one-set, is right? <!--! A:Yes, since the rotation wouldn't happened in different sets-->

Version: v1.0.19 @ 2023.04.04
    finished: Finished the Green calc function; Update the code from v4.1.20; Add the Green calc function(not tested).
    next do : 1.Cross-validation in three band(with interaction and no interaction).
    tinking : How should I add the correction vector for fixing the G calc?

Version: v1.0.20 @ 2023.04.05
    finished: Fix the set_interaction() in impurity class; Change the Impdata data structure; speed up the set_row_primeter_byimpH() function;
    next do : Test the convergence of ground state calc.
    tinking : The Green calc need to fixed for some structure can't find in the sub-space.

Version: v1.0.21 @ 2023.04.06
    finished: Debug for the state class; change for the abge in norg.cpp.
    next do : (same as prev)
    tinking : (same as prev)

Version: v1.0.22 @ 2023.04.06
    finished: fix the if_norg_imp mode, Now debug in this mode.
    next do : try to find the reason energy different with v1.0.07.
    tinking : The number of elerment is same as v1.0.07?

Version: v1.0.23 @ 2023.04.07
    finished: Now the v1.0.23 energy is same as v1.0.07.
    next do : try to fix with rotation imp.
    tinking : is it safe merge n_i↑n_j↓ and n_j↑n_i↓ in one term?<!--! A:Now all the dd-interaction term will divide by 2, since double counting term need to removed.-->

Version: v1.0.24 @ 2023.04.07
    finished: Now the v1.0.24 energy is same as v1.0.07-fixed.
    next do : (same as prev)
    tinking : if there some off-diagonal 4 Fermi term in the H matrix, was not considered? Or overlap?

Version: v1.0.25 @ 2023.04.08
    finished: Find the bug for the anti-commutation in state.cpp Ln:93.
    next do : Test for the Green calc function.
    tinking : In the rotation of the impurity orbital, the energy becomes higher, so the Green calc may be wrong. What about the beginning at no-rotation impurity orbital converge U for rotation impurity orbital?

Version: v1.0.26 @ 2023.04.09
    finished: make some modify and now the if_norg_imp=1 mode can use the if_norg_imp=0 mode's U.
    next do : (same as prev)
    tinking : (same as prev)

Version: v1.0.27 @ 2023.04.10
    finished: Now the Green calc can run, but the valiables are not secutre.
    next do : Cross check the Green calc function with v1.0.07-fixed.
    tinking : The single paritcal states in the Green calc function is correct?

Version: v1.0.28 @ 2023.04.11
    finished: The no-rotation mode imp-orbital fixed.
    next do : (same as prev)
    tinking : (same as prev)

Version: v1.0.29 @ 2023.04.12
    finished: Finished the Green calc function; Now the Calc of Green function is the same in the two modes.
    next do : using this version to test the SrVO3.
    tinking : how to move the code to the Copper-based superconductivity CMDFT calc; And how to move the 2 band calc.

Version: v1.0.30 @ 2023.04.15
    finished: add the "dmft_bethe" for the norg to study the bethe lattice model, but the code is not finished. move from v3.26.1@2022.11.18 version.
    next do : finish the "dmft_bethe" code.
    tinking : (same as prev)

Version: v1.0.31 @ 2023.04.19
    finished: finish the "dmft_bethe" code. but still has some bug, and the code is not tested.<!--! Not finished.-->
    next do : modify for the Zen test KV3Sb5. <!--! force changed--> 
    tinking : (same as prev)

Version: v1.0.32 @ 2023.04.20
    finished: finish the modify.
    next do : Zen test 3-band SrVO3.
    tinking : (same as prev)

Version: v1.0.33 @ 2023.04.21
    finished: modify for no-rotation impurity orbital mode;
    next do : 1.test the different between rotation and no-rotation impurity orbital mode in 3band imp model; 2.calc the KV3Sb5 in no-rotation mode with 4bath ed.
    tinking : (same as prev)

Version: v1.0.34 @ 2023.04.21
    finished: bug fixed for the NORG orbital.densitymatrix.cpp Ln337-347. <!--! IMPORTANT --> 
    next do : (same as prev)
    tinking : Why would you forget the the NORG orbital order in densitymatrix.cpp !?

Version: v1.0.35 @ 2023.04.21
    finished: upgrade, add the share memory for speed up reason.
    next do : 1.test the different between rotation and no-rotation impurity orbital mode in 3band imp model;
    tinking : (same as prev)

Version: v1.0.36 @ 2023.04.22
    finished: modify for test the 3band and KVSb.
    next do : test the code with ZEN(2a;KVSb)
    tinking : what's the physical of KVSb?

Version: v1.0.37 @ 2023.04.24 <!--! NAME: Version: v1.1.00 --> 
    finished: 1. finished the Bug finding in densitymatrix.cpp and prmt.cpp for even I2B number; 2. upgraded the crrvec function for green calc. 3. upgrade the norg.cpp set_row_primeter_byimpH() function for share memory.
    next do : Using no special imp(*) orbital to modify the code.
    thinking: what if the impurity interaction acting on the right? (not the left)

Version: v1.1.01 @ 2023.04.25
    finished: 1.upgrade the crrvec.cpp .h; 2. upgrade the apizen for read [-1 -2 -3  3  2  1] restrain.
    next do : (same as prev)
    thinking: (same as prev)

Version: v1.1.02 @ 2023.04.26
    finished: 1. finish the first version of the NORG for using [-1 -2 -3  3  2  1] restrain; 
    next do : 1.modify the code for using the col restrain to calc the dim; 2.debug the code for the cpnooc mode.
    thinking: How to update the bethe lattice model? and how to study the half-filling hubbard model case for multi-band?

Version: v1.1.03 @ 2023.04.27
    finished: 1.densitymatirx.cpp: Fixed the bug for dm build; 2.Using the col restrain to calc the dim; 3. fix the cpnooc and cnooc mode.
    next do : 1.update the bethe lattice model.
    thinking: (same as prev)

Version: v1.1.04 @ 2023.04.27
    finished: Fix the bug for no-Rimp mode, R mode ED benchmarked with v1.0.37 and get the energy also same as v1.0.07.
    next do : 1.update the bethe lattice model.
    thinking: (same as prev)

Version: v1.1.05 @ 2023.05.01
    finished: modify the according_nppso() function in prmtr.cpp for the no-half-filling case. 
    next do : 1.update the bethe lattice model.
    thinking: (same as prev)

Version: v1.1.06 @ 2023.05.04
    finished: 1.BUG fixed: crrltfun.cpp; 2. add the "dmft_bethe" calc function for multi-band system.
    next do : going to add the no-half-filling case for the bethe lattice model.
    thinking: What's the physical for the calc of the no-half-filling case?<!--! (Read A.Koga2004prl) --> 

Version: v1.1.07 @ 2023.05.05
    finished: 1.Find the bug for using U(ni-1/2)(nj-1/2) symmetry; 
    next do : 1.testing the half-filling case for the bethe lattice model. with u3d0.3; 2. add the no-half-filling case for the bethe lattice model.
    thinking: (same as prev)

Version: v1.1.08 @ 2023.05.06
    finished: 1.finish the benchmark with p3v26.1;
    next do : 1.testing the code in BSCC-T6; 2. add the no-half-filling case for the bethe lattice model.
    thinking: (same as prev)

Version: v1.1.09 @ 2023.05.08
    finished: 1.adding the no-half-filling case for the bethe lattice model.
    next do : testing the code in BSCC-T6;
    thinking: (same as prev)

Version: v1.1.10 @ 2023.05.10
    finished: 1.fix the code for calc the 1 band Hubbard model.
    next do : testing 1-band the code in BSCC-T6;
    thinking: (same as prev)

Version: v1.1.11 @ 2023.05.10
    finished: 1.add the degenerate ground state calc.
    next do : testing 1-band the code in BSCC-T6;
    thinking: (same as prev)

Version: v1.1.11 @ 2023.05.11
    finished: Using the sgm iteration for the behte lattice iteration.
    next do : testing 1- or 2-band calc in BSCC-T6;
    thinking: (same as prev)

Version: v1.1.12 @ 2023.05.11
    finished: bug fix for mb.gfimp calc.
    next do : testing 1- or 2-band calc in BSCC-T6;
    thinking: (same as prev)

Version: v1.1.13 @ 2023.05.16
    finished: 1. add the 1-band Degenerate energy levels test. 2. also can auto judge the degenerate energy levels.
    next do : testing 1- or 2-band calc in BSCC-T6;
    thinking: (same as prev)

Version: v1.1.14 @ 2023.05.17
    finished: 1. add the norg.lock rule for sleep the NORG program for APIzen class.
    next do : (same as prev)
    thinking: (same as prev)

beta-Version: 1.1.13.1 @ 2023.05.26
    finished: 1.add the find_gloc_by_se for finding the gloc by the self-energy in bethe lattice; 2. cancel the pre-judge system in different partical sub space; 3.modify some calculation in lanczos.h; 4. modify some print out.
    next do : modify the fitting.
    thinking: To get smooth DOS did we need to move the fitting on retarded green function?

beta-Version: 1.1.13.2 @ 2023.05.28
    realized: In put the ose prameter and not change ose.
    next do : using the partical-hole symmetry to fit.
    thinking: what if we cann't use partical-hole symmetry.

beta-Version: 1.1.13.3 @ 2023.05.29
    realized: change back for change the ose parmeter.
    next do : using the bath sum rule.
    thinking: (same as prev)

beta-Version: 1.1.13.4 @ 2023.05.29
    realized: adding the bath sum rule in the fitting coding
    next do : try to add the hoping regularization for the fitting code.
    thinking: how to enlarge the bath number without the thought fitting.

beta-Version: 1.1.13.5 @ 2023.06.05
    realized: adding the regE and regV in the fitting.
    next do : try to add the partical-hole symmary in fitting.
    thinking: What's the physical for the calc of the no-half-filling case?

beta-Version: 1.1.13.6 @ 2023.06.09
    realized: 1. modify for the DOI: 10.1103/PhysRevB.100.085104, for green function we only consider one spanless orbital; 2. change the Type for the final_ground_state(Now we only have the once lowest_eigpairs() happened).
    next do : add the Pulay mixing
    thinking: (same as prev)

beta-Version: 1.1.13.7 @ 2023.06.09
    realized: Fixed the 1.1.13.6's bug.
    next do : add the Pulay mixing
    thinking: (same as prev)

beta-Version: 1.1.13.9 @ 2023.06.19
    realized: 08:add the pulay_mixing function(NOT tested); 09: add the even and odd subspace calc green.
    next do : test for the new space.
    thinking: What's the physical for the calc of the no-half-filling case? Why the mott insulator will degeneracy.

Version: v1.1.15 @ 2023.06.25
    realized: 1. Add the <n_i n_j> calc; 2. Return the 1.1.13.6 for main calculation.
    next do : bench Cross-Validation with 1.1.13.6
    thinking: Why would <n_i n_i> same as <n_i>?

Version: v1.2.0 @ 2023.06.30
    realized: 1. Implement Lanczos full parallelization; 2.Implement fast search in the multi-particle number space.
    next do : update for the ZenAPI class
    thinking: What are the physical properties of the La3Ni2O7 material?

Version: v1.2.1 @ 2023.07.07
    realized: update for the apizen.cpp
    next do : test the new fitting code with dop driveing.
    thinking: (same as prev)

Version: v1.2.2 @ 2023.07.14
    realized: add the <s_z,i s_z,j> and <n_i n_j> calc.
    next do : try on the ZEN's iteration.
    thinking: (same as prev)

Version: v1.2.3 @ 2023.07.24
    realized: add the <S_z^2> and <S^2> calc.
    next do : try to initialize the orbital set from HFA transform.
    thinking: if the HFA transform worked?

Version: v1.2.4 @ 2023.08.08
    realized: upgrade for the fitting.
    next do : test on the ZEN
    thinking: if the HFA transform worked?