#include "CoolProp.h"
#include <iostream>
#include <cstdlib>
struct FluidState {
        double P;
        double T;
        double v;
        double d;
        double h;
        double s;
        double u;
        double cv;
        double cp;
        double c;
        double alpha;
        double beta;
        double zeta;
        double eta;
        double lambda;
        int i;
        int j;
        int phase;
        double dlam_dT;
        double dlam_drho;
        double deta_dT;
        double deta_drho;
        double dPdrho_e;
        double dPde_rho;
        double dTdrho_e;
        double dTde_rho;
        double dhdrho_P;
        double dhdP_rho;
        double dsdrho_P;
        double dsdP_rho;
};

using namespace std;
double calc_derivative(string property, string withrespect_to, string at_constant, string InputSpec, double input1, double input2, string fluid_name){
     
    double fph, fmh;
    double eps=0.0001;
    if (string(1,InputSpec[0])==withrespect_to) {
    	fph = CoolProp::PropsSI(property, string(1,InputSpec[0]), input1+.5*eps, string(1,InputSpec[1]), input2, fluid_name);
	fmh = CoolProp::PropsSI(property, string(1,InputSpec[0]), input1-.5*eps, string(1,InputSpec[1]), input2, fluid_name);
    }
    else if (string(1,InputSpec[1])==withrespect_to) {
    	fph = CoolProp::PropsSI(property, string(1,InputSpec[0]), input1, string(1,InputSpec[1]), input2+.5*eps, fluid_name);
	fmh = CoolProp::PropsSI(property, string(1,InputSpec[0]), input1, string(1,InputSpec[1]), input2-.5*eps, fluid_name);
    }
    return (fph-fmh)/eps;
}
void coolprop_allprops_su2(string InputSpec, string fluid_name, double input1, double input2, struct FluidState &state){
    state.P=CoolProp::PropsSI("P", string(1,InputSpec[0]), input1, string(1,InputSpec[1]), input2, fluid_name);
    state.T=CoolProp::PropsSI("T", string(1,InputSpec[0]), input1, string(1,InputSpec[1]), input2, fluid_name);
    state.d=CoolProp::PropsSI("D", string(1,InputSpec[0]), input1, string(1,InputSpec[1]), input2, fluid_name);
    state.v=1.0/state.d;
    state.h=CoolProp::PropsSI("H", string(1,InputSpec[0]), input1, string(1,InputSpec[1]), input2, fluid_name);
    state.s=CoolProp::PropsSI("S", string(1,InputSpec[0]), input1, string(1,InputSpec[1]), input2, fluid_name);
    state.u=CoolProp::PropsSI("U", string(1,InputSpec[0]), input1, string(1,InputSpec[1]), input2, fluid_name);
    state.cv=CoolProp::PropsSI("CVMASS", string(1,InputSpec[0]), input1, string(1,InputSpec[1]), input2, fluid_name);
    state.cp=CoolProp::PropsSI("CPMASS", string(1,InputSpec[0]), input1, string(1,InputSpec[1]), input2, fluid_name);
    state.c=CoolProp::PropsSI("A", string(1,InputSpec[0]), input1, string(1,InputSpec[1]), input2, fluid_name);
    state.eta=CoolProp::PropsSI("V", string(1,InputSpec[0]), input1, string(1,InputSpec[1]), input2, fluid_name);
    state.lambda=CoolProp::PropsSI("L", string(1,InputSpec[0]), input1, string(1,InputSpec[1]), input2, fluid_name);
    state.phase=CoolProp::PropsSI("PHASE", string(1,InputSpec[0]), input1, string(1,InputSpec[1]), input2, fluid_name);
    state.dlam_dT=calc_derivative("L", "T", "D", InputSpec, input1, input2, fluid_name);
    state.dlam_drho=calc_derivative("L", "D", "T", InputSpec, input1, input2, fluid_name);
    state.deta_dT=calc_derivative("V", "T", "D", InputSpec, input1, input2, fluid_name);
    state.deta_drho=calc_derivative("V", "D", "T", InputSpec, input1, input2, fluid_name);
    state.dPdrho_e=CoolProp::PropsSI("d(P)/d(D)|U", string(1,InputSpec[0]), input1, string(1,InputSpec[1]), input2, fluid_name);
    state.dPde_rho=CoolProp::PropsSI("d(P)/d(U)|D", string(1,InputSpec[0]), input1, string(1,InputSpec[1]), input2, fluid_name);
    state.dTdrho_e=CoolProp::PropsSI("d(T)/d(D)|U", string(1,InputSpec[0]), input1, string(1,InputSpec[1]), input2, fluid_name);
    state.dTde_rho=CoolProp::PropsSI("d(T)/d(U)|D", string(1,InputSpec[0]), input1, string(1,InputSpec[1]), input2, fluid_name);
    state.dhdrho_P=CoolProp::PropsSI("d(H)/d(D)|P", string(1,InputSpec[0]), input1, string(1,InputSpec[1]), input2, fluid_name);
    state.dhdP_rho=CoolProp::PropsSI("d(H)/d(P)|D", string(1,InputSpec[0]), input1, string(1,InputSpec[1]), input2, fluid_name);
    state.dsdrho_P=CoolProp::PropsSI("d(S)/d(D)|P", string(1,InputSpec[0]), input1, string(1,InputSpec[1]), input2, fluid_name);
    state.dsdP_rho=CoolProp::PropsSI("d(S)/d(P)|D", string(1,InputSpec[0]), input1, string(1,InputSpec[1]), input2, fluid_name);
}



int main()
{
    // First type (slowest, due to most string processing, exposed in DLL)
    FluidState *state = new FluidState;
    string InputSpec = "TD";
    string fluid_name = "Toluene";
    coolprop_allprops_su2( InputSpec, fluid_name, 500., .1,  *state);
        cout << "P: " << state->P << endl;
        cout << "T: " << state->T << endl;
        cout << "v: " << state->v << endl;
        cout << "d: " << state->d << endl;
        cout << "h: " << state->h << endl;
        cout << "s: " << state->s << endl;
        cout << "u: " << state->u << endl;
        cout << "cv: " << state->cv << endl;
        cout << "cp: " << state->cp << endl;
        cout << "c: " << state->c << endl;
        cout << "alpha: " << state->alpha << endl;
        cout << "beta: " << state->beta << endl;
        cout << "zeta: " << state->zeta << endl;
        cout << "eta: " << state->eta << endl;
        cout << "lambda: " << state->lambda << endl;
        cout << "i: " << state->i << endl;
        cout << "j: " << state->j << endl;
        cout << "phase: " << state->phase << endl;
        cout << "dlam_dT: " << state->dlam_dT << endl;
        cout << "dlam_drho: " << state->dlam_drho << endl;
        cout << "deta_dT: " << state->deta_dT << endl;
        cout << "deta_drho: " << state->deta_drho << endl;
        cout << "dPdrho_e: " << state->dPdrho_e << endl;
        cout << "dPde_rho: " << state->dPde_rho << endl;
        cout << "dTdrho_e: " << state->dTdrho_e << endl;
        cout << "dTde_rho: " << state->dTde_rho << endl;
        cout << "dhdrho_P: " << state->dhdrho_P << endl;
        cout << "dhdP_rho: " << state->dhdP_rho << endl;
        cout << "dsdrho_P: " << state->dsdrho_P << endl;
        cout << "dsdP_rho: " << state->dsdP_rho << endl;
    return EXIT_SUCCESS;

}


//
//void createTable()
//{
//    double Tmin = 300.;//DoubleParam("TABLE_TMIN");
//    double Tmax = 400.;//oubleParam("TABLE_TMAX");
//    double rhomin = 0.1;//getDoubleParam("TABLE_RHOMIN");
//    double rhomax = 10.;//getDoubleParam("TABLE_RHOMAX");
//
//    imax = 100//getIntParam("TABLE_IMAX");
//    jmax = 100//getIntParam("TABLE_JMAX");
//
//    // ============================== //
//    //        Generate table(s)       //
//    // ============================== //
//    int method = 0;//getIntParam("INTERPOLATION_SCHEME", 0); // 0=bilinear, 1=polynomial
//    tab_split = 0;//getBoolParam("TABLE_SPLIT", 0);
//    tab_dist = "LOG";//getStringParam("TABLE_DISTR", "UNIFORM"); // UNIFORM, LOG
//
//
//    if (method==0)        intScheme="BILINEAR";
//
//    // initialize the table
//    state = new FluidState*[imax];
//    for (int i=0; i<imax; i++)
//      state[i] = new FluidState[jmax];
//
//
//}
//




