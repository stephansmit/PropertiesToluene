#include <iostream>
#include <fstream>
using namespace std;
#include "../../SU2-fork/Common/include/mpi_structure.hpp"
#include "../../SU2-fork/SU2_CFD/include/fluid_model.hpp"
#include "../../SU2-fork/SU2_CFD/src/fluid_model_pig.cpp"
#include "../../SU2-fork/SU2_CFD/src/fluid_model_ppr.cpp"
#include "../../SU2-fork/SU2_CFD/src/fluid_model_pvdw.cpp"
#include "../../SU2-fork/SU2_CFD/src/fluid_model.cpp"
#include "../../SU2-fork/SU2_CFD/src/transport_model.cpp"
#include "../../SU2-fork/SU2_CFD/include/transport_model.hpp"
#include "../../SU2-fork/SU2_CFD/src/transport_model_toluene.cpp"
#include "properties_table_su2.hpp"
#include "properties_table_su2.cpp"










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
    su2double s = 110.4;			//sutherland constant
    su2double t_ref =273.15;		//reference temperature sutherland

    //transport propert
    CViscosityToluene *ViscocityModelToluene = new CViscosityToluene();
    CConductivityToluene *ConductivityModelToluene = new CConductivityToluene();

   //fluid properties
    CIdealGas *FluidModelIG = new CIdealGas(gamma, R);
    CPengRobinson *FluidModelPR = new CPengRobinson(gamma, R, Pstar, Tstar, w);

    //tables
    CPropertiesTableSU2 *TablePR = new CPropertiesTableSU2(FluidModelPR, ConductivityModelToluene, ViscocityModelToluene);
    CPropertiesTableSU2 *TableIG = new CPropertiesTableSU2(FluidModelIG, ConductivityModelToluene, ViscocityModelToluene);

    //writing tables
    TablePR->GenerateTable_PT("../Tables/ToluenePR_PT.txt",18e5, 0.1e5, 180, 600, 480 , 340);
    TablePR->GenerateTable_rhoT("../Tables/ToluenePR_rhoT.txt",100, 0.1, 180, 600, 480 , 340);
    TableIG->GenerateTable_PT("../Tables/TolueneIG_PT.txt",18e5, 0.1e5, 180, 600, 480 , 340);
    TableIG->GenerateTable_rhoT("../Tables/TolueneIG_rhoT.txt",100, 0.1, 180, 600, 480 , 340);


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
