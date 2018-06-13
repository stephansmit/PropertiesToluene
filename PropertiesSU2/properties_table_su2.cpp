#include "properties_table_su2.hpp"


void CPropertiesTableSU2::GenerateTable_PT(const char* filename,
										   su2double Pmax,
										   su2double Pmin,
										   int Pn,
										   su2double Tmax,
										   su2double Tmin,
										   int Tn) {

	su2double P, T, e, rho, s, cp, cv, h, mu, k, c,dkdT_rho, dkdrho_T, dmudT_rho, dmudrho_T;
	su2double dsdP_rho, dsdrho_P, dhdP_rho, dhdrho_P;
	double DP, DT;
	ofstream file;

	DT= (Tmax-Tmin)/(Tn-1);
	DP= (Pmax-Pmin)/(Pn-1);
	cout << "Generating table: " << filename << '\n';

	file.open (filename);
	file << "P\tT\trho\tmu\tk\tcp\te\ts\tc\th\tdkdT_rho\tdkdrho_T\tdmudT_rho\tdmudrho_T\tdsdrho_P\tdsdP_rho\tdhdrho_P\tdhdP_rho\n";

	P = Pmin - DP;
	for (int i=0; i<Pn; i++){
	   P = P + DP;
	   T = Tmin - DT;
	   for (int j=0; j<Tn; j++){
          T = T + DT;

		  FluidModel->SetTDState_PT(P,T);
		  rho = FluidModel->GetDensity();
		  FluidModel->ComputeDerivativeNRBC_Prho(P,rho);
		  mu = FluidModel->GetLaminarViscosity();
		  k = FluidModel->GetThermalConductivity();
		  cp = FluidModel->GetCp();
		  e = FluidModel->GetStaticEnergy();
		  s = FluidModel->GetEntropy();
		  dsdP_rho = FluidModel->GetdsdP_rho();
		  dsdrho_P = FluidModel->Getdsdrho_P();
		  dhdrho_P = FluidModel->Getdhdrho_P();
		  dhdP_rho = FluidModel->GetdhdP_rho();
		  h = e + P/rho;
		  c = FluidModel->GetSoundSpeed();
		  dkdT_rho = FluidModel->GetdktdT_rho();
		  dkdrho_T = FluidModel->Getdktdrho_T();
		  dmudT_rho = FluidModel->GetdmudT_rho();
		  dmudrho_T = FluidModel->Getdmudrho_T();
		  dsdrho_P = FluidModel->Getdsdrho_P();
		  dsdP_rho = FluidModel->GetdsdP_rho();
		  dhdrho_P = FluidModel->Getdhdrho_P();
		  dhdP_rho = FluidModel->GetdhdP_rho();

		  file << P/100000. << '\t'
			   << T <<  '\t'
			   << rho<< '\t'
			   << mu << '\t'
			   << k  << '\t'
			   << cp << '\t'
			   << e <<  '\t'
			   << s <<  '\t'
			   << c <<  '\t'
			   << h <<  '\t'
			   << dkdT_rho <<'\t'
			   << dkdrho_T<<'\t'
			   << dmudT_rho <<'\t'
			   << dmudrho_T<< '\t'
			   << dsdrho_P<<'\t'
			   << dsdP_rho <<'\t'
			   << dhdrho_P <<'\t'
			   << dhdP_rho<<
			   '\n';
	   }
	}
	file.close();
}

void CPropertiesTableSU2::GenerateTable_rhoT(const char* filename,
										   su2double rhoMax,
										   su2double rhoMin,
										   int rhoN,
										   su2double Tmax,
										   su2double Tmin,
										   int Tn) {

	su2double P, T, e, rho, s, cp, cv, h, mu, k, c, dkdT_rho, dkdrho_T, dmudT_rho, dmudrho_T;
	su2double dsdP_rho, dsdrho_P, dhdP_rho, dhdrho_P;

	double DR, DT;
	ofstream file;
	DT= (Tmax-Tmin)/(Tn-1);
	DR= (rhoMax-rhoMin)/(rhoN-1);
	cout << "Generating table: " << filename << '\n';
	file.open (filename);
	file << "rho\tT\tP\tmu\tk\tcp\th\ts\tc\te\tdkdT_rho\tdkdrho_T\tdmudT_rho\tdmudrho_T\tdsdrho_P\tdsdP_rho\tdhdrho_P\tdhdP_rho\n";

	rho = rhoMax - DR;
	for (int i=0; i<rhoN; i++){
	   rho = rho + DR;
	   T = Tmin - DT;
	   for (int j=0; j<Tn; j++){
          T = T + DT;

		  FluidModel->SetTDState_rhoT(rho,T);
		  P = FluidModel->GetPressure();
		  FluidModel->ComputeDerivativeNRBC_Prho(P,rho);
		  mu = FluidModel->GetLaminarViscosity();
		  k = FluidModel->GetThermalConductivity();
		  cp = FluidModel->GetCp();
		  e = FluidModel->GetStaticEnergy();
		  s = FluidModel->GetEntropy();
		  c = FluidModel->GetSoundSpeed();
		  h = e + P/rho;
		  dkdT_rho = FluidModel->GetdktdT_rho();
		  dkdrho_T = FluidModel->Getdktdrho_T();
		  dmudT_rho = FluidModel->GetdmudT_rho();
		  dmudrho_T = FluidModel->Getdmudrho_T();
		  dsdrho_P = FluidModel->Getdsdrho_P();
		  dsdP_rho = FluidModel->GetdsdP_rho();
		  dhdrho_P = FluidModel->Getdhdrho_P();
		  dhdP_rho = FluidModel->GetdhdP_rho();

		  file << rho <<'\t'
			   << T <<'\t'
			   << P/100000.<<'\t'
			   << mu  <<'\t'
			   << k   <<'\t'
			   << cp  <<'\t'
			   << e   <<'\t'
			   << s   <<'\t'
			   << c   <<'\t'
			   << h   <<'\t'
			   << dkdT_rho <<'\t'
			   << dkdrho_T<<'\t'
			   << dmudT_rho <<'\t'
			   << dmudrho_T<< '\t'
			   << dsdrho_P<<'\t'
			   << dsdP_rho <<'\t'
			   << dhdrho_P <<'\t'
			   << dhdP_rho<<
			   '\n';
	   }
	}
	file.close();
}
