#include <iostream>
#include <cstdlib>
#include "../../SU2-fork/Common/include/mpi_structure.hpp"
#include "../../SU2-fork/SU2_CFD/include/fluid_model.hpp"
#include "../../SU2-fork/SU2_CFD/include/look_up_table.hpp"
#include "../../SU2-fork/SU2_CFD/src/fluid_model_pig.cpp"
#include "../../SU2-fork/SU2_CFD/src/look_up_table.cpp"
#include "../../SU2-fork/SU2_CFD/src/fluid_model_lut.cpp"
#include "../../SU2-fork/SU2_CFD/src/fluid_model_ppr.cpp"
#include "../../SU2-fork/SU2_CFD/src/fluid_model_pvdw.cpp"
#include "../../SU2-fork/SU2_CFD/src/fluid_model.cpp"
#include "../../SU2-fork/SU2_CFD/src/fluid_model_cp.cpp"
#include "../../SU2-fork/SU2_CFD/src/transport_model.cpp"
#include "../../SU2-fork/SU2_CFD/include/transport_model.hpp"
#include "../../SU2-fork/SU2_CFD/src/transport_model_toluene.cpp"
#include "../../SU2-fork/SU2_CFD/src/transport_model_lut.cpp"
#include "../../SU2-fork/SU2_CFD/src/transport_model_cp.cpp"






int main() 
{
    su2double gamma = 1.06;			//
    su2double R = 90.23;			//
    su2double Pstar = 4126300.0; 	//critical pressure toluene
    su2double Tstar = 591.75;		//critical temperature toluene
    su2double w = 0.2657;
    su2double kt_const = 0.08029;
    su2double pr_const = 1;
    su2double mu_ref = 1.716E-5;	//reference viscocity sutherland
    su2double t_ref =273.15;		//reference temperature sutherland
    su2double rho_min = 0.005;
    su2double rho_max = 145.;
    su2double T_min = 310.0;
    su2double T_max = 690.0;  
    bool createTable = 0;
    ////transport propert
    //CViscosityToluene *ViscocityModelToluene = new CViscosityToluene();
    //CConductivityToluene *ConductivityModelToluene = new CConductivityToluene();
    CLUTFluidModel *LookUpTable = new CLUTFluidModel("table","Toluene", "LOG", 400,400,rho_min, rho_max, T_min, T_max, "BILINEAR", createTable);
    CLUTFluidModel *LookUpTable2 = new CLUTFluidModel("table","Toluene", "LOG", 400,400,rho_min, rho_max, T_min, T_max, "BILINEAR", createTable);
    CLUTFluidModel *LookUpTable3 = new CLUTFluidModel("table","Toluene", "LOG", 400,400,rho_min, rho_max, T_min, T_max, "BILINEAR", createTable);
    CLUTFluidModel *LookUpTable4 = new CLUTFluidModel("table","Toluene", "LOG", 400,400,rho_min, rho_max, T_min, T_max, "BILINEAR", createTable);
    CLUTFluidModel *LookUpTable5 = new CLUTFluidModel("table","Toluene", "LOG", 400,400,rho_min, rho_max, T_min, T_max, "BILINEAR", createTable);
    CLUTFluidModel *LookUpTable6 = new CLUTFluidModel("table","Toluene", "LOG", 400,400,rho_min, rho_max, T_min, T_max, "BILINEAR", createTable);
    CCPFluidModel *CoolProp = new CCPFluidModel("Toluene");
    CConductivityCP *conduct = new CConductivityCP("Toluene");
    CViscosityCP *visc = new CViscosityCP("Toluene");
    CoolProp->SetThermalConductivityModelDirect(conduct);
    CoolProp->SetLaminarViscosityModelDirect(visc);

    LookUpTable->SetTransportModelsLUTDirect();
    LookUpTable2->SetTransportModelsLUTDirect();
    LookUpTable3->SetTransportModelsLUTDirect();
    LookUpTable4->SetTransportModelsLUTDirect();
    LookUpTable5->SetTransportModelsLUTDirect();
    LookUpTable6->SetTransportModelsLUTDirect();


    
    su2double h, s, P, T, rho, e, k;


    LookUpTable->SetTDState_rhoT(145,690);
    cout << LookUpTable->GetPressure() << '\n';
    cout << LookUpTable->GetLaminarViscosity() << '\n';
    
    h =LookUpTable->GetStaticEnergy() +  LookUpTable->GetPressure()/LookUpTable->GetDensity(); 
    s =LookUpTable->GetEntropy();
    P =LookUpTable->GetPressure();
    T =LookUpTable->GetTemperature();
    rho =LookUpTable->GetDensity();
    e =LookUpTable->GetStaticEnergy();
    k =LookUpTable->GetThermalConductivity();
    
    
    LookUpTable2->SetTDState_Prho(P,rho);
    cout << LookUpTable2->GetPressure() << '\n';
    cout << LookUpTable2->GetTemperature() << '\n';
    cout << LookUpTable2->GetDensity() << '\n';
    cout << LookUpTable2->GetLaminarViscosity() << '\n';
    LookUpTable3->SetTDState_rhoe(rho,e);
    cout << LookUpTable3->GetPressure() << '\n';
    cout << LookUpTable3->GetTemperature() << '\n';
    cout << LookUpTable3->GetDensity() << '\n';
    cout << LookUpTable3->GetLaminarViscosity() << '\n';
    LookUpTable4->SetTDState_PT(P,T);
    cout << LookUpTable4->GetPressure() << '\n';
    cout << LookUpTable4->GetTemperature() << '\n';
    cout << LookUpTable4->GetDensity() << '\n';
    cout << LookUpTable4->GetLaminarViscosity() << '\n';
    LookUpTable5->SetTDState_Ps(P,s);
    cout << LookUpTable5->GetPressure() << '\n';
    cout << LookUpTable5->GetTemperature() << '\n';
    cout << LookUpTable5->GetDensity() << '\n';
    cout << LookUpTable5->GetLaminarViscosity() << '\n';
    LookUpTable6->SetTDState_hs(h,s);
    cout << LookUpTable6->GetPressure() << '\n';
    cout << LookUpTable6->GetTemperature() << '\n';
    cout << LookUpTable6->GetDensity() << '\n';
    cout << LookUpTable6->GetLaminarViscosity() << '\n';


    cout << T << '\t' << h << '\t' << s << '\t'<< P << '\t'<< e << '\n';
    //CoolProp->SetTDState_rhoT(0.05,488);
    //CoolProp->SetTDState_rhoT(rho_min,T_min);
    //cout << CoolProp->GetEntropy() << '\n';
    //cout << CoolProp->GetPressure() << '\n';
    //CoolProp->SetTDState_rhoT(rho_max,T_min);
    //cout << CoolProp->GetEntropy() << '\n';
    //cout << CoolProp->GetPressure() << '\n';
    //CoolProp->SetTDState_rhoT(rho_min,T_max);
    //cout << CoolProp->GetEntropy() << '\n';
    //cout << CoolProp->GetPressure() << '\n';
    //CoolProp->SetTDState_rhoT(rho_max,T_max);
    //cout << CoolProp->GetEntropy() << '\n';
    //cout << CoolProp->GetPressure() << '\n';




    //h =CoolProp->GetStaticEnergy() +  CoolProp->GetPressure()/CoolProp->GetDensity(); 
    //cout << h << endl;
    //Set rhoT
    //CoolProp->SetTDState_rhoT(2,500);
    //cout << CoolProp->GetLaminarViscosity() << '\n';
    //P = CoolProp->GetPressure ();
    //P = CoolProp->GetSoundSpeed ();
    //P = CoolProp->GetSoundSpeed2 ();
    //P = CoolProp->GetDensity ();
    //P = CoolProp->GetEntropy ();
    //P = CoolProp->GetStaticEnergy ();
    //P = CoolProp->GetTemperature ();
    //P = CoolProp->GetCp ();
    //P = CoolProp->GetdPdrho_e ();
    //P = CoolProp->GetdPde_rho ();
    //P = CoolProp->GetdTdrho_e ();
    //P = CoolProp->GetdTde_rho ();
    //P = CoolProp->Getdhdrho_P ();
    //P = CoolProp->GetdhdP_rho ();
    //P = CoolProp->Getdsdrho_P ();
    //P = CoolProp->GetdsdP_rho ();
    //P = CoolProp->GetLaminarViscosity();
    //P = CoolProp->Getdmudrho_T ();
    //P = CoolProp->GetdmudT_rho ();
    //P = CoolProp->GetThermalConductivity();
    //P = CoolProp->Getdktdrho_T ();
    //P = CoolProp->GetdktdT_rho ();

    //h =CoolProp->GetStaticEnergy() +  LookUpTable->GetPressure()/LookUpTable->GetDensity(); 
    //s =CoolProp->GetEntropy();
    //P =CoolProp->GetPressure();
    //T =CoolProp->GetTemperature();
    //rho =CoolProp->GetDensity();
    //e =CoolProp->GetStaticEnergy();
    //k =CoolProp->GetThermalConductivity();

    //CoolProp->SetTDState_rhoT(2,500);
    //cout << CoolProp->GetLaminarViscosity() << '\n';
    //
    //
    ////set hs
    //CoolProp->SetTDState_hs(h,s);
    //cout << CoolProp->GetLaminarViscosity() << '\n';
    //CoolProp->SetTDState_rhoT(2,500);
    //cout << CoolProp->GetLaminarViscosity() << '\n';
   
    ////set PT
    //CoolProp->SetTDState_PT(P,T);
    //cout << CoolProp->GetLaminarViscosity() << '\n';
    //CoolProp->SetTDState_rhoT(2,500);
    //cout << CoolProp->GetLaminarViscosity() << '\n';

    ////Set rhoe
    //CoolProp->SetTDState_rhoe(rho,e);
    //cout << CoolProp->GetLaminarViscosity() << '\n';
    //CoolProp->SetTDState_rhoT(2,500);
    //cout << CoolProp->GetLaminarViscosity() << '\n';
    //
    ////Set Ps
    //CoolProp->SetTDState_Ps(P,s);
    //cout << CoolProp->GetLaminarViscosity() << '\n';
    //CoolProp->SetTDState_rhoT(2,500);
    //cout << CoolProp->GetLaminarViscosity() << '\n';

    ////Set Prho
    //CoolProp->SetEnergy_Prho(P,rho);
    //cout << CoolProp->GetLaminarViscosity() << '\n';


   ////fluid properties
    //CIdealGas *FluidModelIG = new CIdealGas(gamma, R);
    //CPengRobinson *FluidModelPR = new CPengRobinson(gamma, R, Pstar, Tstar, w);

    ////tables
    //CPropertiesTableSU2 *TablePR = new CPropertiesTableSU2(FluidModelPR, ConductivityModelToluene, ViscocityModelToluene);
    //CPropertiesTableSU2 *TableIG = new CPropertiesTableSU2(FluidModelIG, ConductivityModelToluene, ViscocityModelToluene);

    ////writing tables
    //TablePR->GenerateTable_PT("../Tables/ToluenePR_PT.txt",18e5, 0.1e5, 180, 600, 480 , 340);
    //TablePR->GenerateTable_rhoT("../Tables/ToluenePR_rhoT.txt",100, 0.1, 180, 600, 480 , 340);
    //TableIG->GenerateTable_PT("../Tables/TolueneIG_PT.txt",18e5, 0.1e5, 180, 600, 480 , 340);
    //TableIG->GenerateTable_rhoT("../Tables/TolueneIG_rhoT.txt",100, 0.1, 180, 600, 480 , 340);


//    FluidModelPR->SetThermalConductivityModel2(ViscocityModelToluene);
//    CVanDerWaalsGas *FluidModelVDW = new CVanDerWaalsGas(gamma, R, Pstar, Tstar);



//    su2double T, rho;
//    T=300.0;rho=0.0;
//    ViscocityModelToluene->SetViscosity(T,rho);
//    cout << ViscocityModelToluene->GetViscosity() << '\n';
//    T=400.0;rho=0.0;
//    ViscocityModelToluene->SetViscosity(T,rho);
//    cout << ViscocityModelToluene->GetViscosity() << '\n';
//    T=550.0;rho=0.0;
//    ViscocityModelToluene->SetViscosity(T,rho);
//    cout << ViscocityModelToluene->GetViscosity() << '\n';
//    T=300.0;rho=865.0;
//    ViscocityModelToluene->SetViscosity(T,rho);
//    cout << ViscocityModelToluene->GetViscosity() << '\n';
//    T=400.0;rho=770.0;
//    ViscocityModelToluene->SetViscosity(T,rho);
//    cout << ViscocityModelToluene->GetViscosity() << '\n';
//    T=550.0;rho=550.0;
//    ViscocityModelToluene->SetViscosity(T,rho);
//    cout << ViscocityModelToluene->GetViscosity() << '\n';
//

    return 0;

}
