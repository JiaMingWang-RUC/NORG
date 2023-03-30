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