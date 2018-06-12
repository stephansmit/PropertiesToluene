#include "properties_table_su2.hpp"


void CPropertiesTableSU2::GenerateTable_PT(const char* filename,
										   su2double Pmax,
										   su2double Pmin,
										   int Pn,
										   su2double Tmax,
										   su2double Tmin,
										   int Tn) {

	su2double P, T, e, rho, s, cp, cv, h, mu, k, c, dkT, dkrho, dmuT, dmurho;
	double DP, DT;
	ofstream file;

	DT= (Tmax-Tmin)/(Tn-1);
	DP= (Pmax-Pmin)/(Pn-1);
	cout << "Generating table: " << filename << '\n';

	file.open (filename);
	file << "P\tT\trho\tmu\tk\tcp\th\ts\tc\te\tdkT\tdkrho\tdmuT\tdmurho\n";

	P = Pmin - DP;
	for (int i=0; i<Pn; i++){
	   P = P + DP;
	   T = Tmin - DT;
	   for (int j=0; j<Tn; j++){
          T = T + DT;

		  FluidModel->SetTDState_PT(P,T);
		  rho = FluidModel->GetDensity();
		  mu = FluidModel->GetLaminarViscosity();
		  k = FluidModel->GetThermalConductivity();
		  cp = FluidModel->GetCp();
		  e = FluidModel->GetStaticEnergy();
		  s = FluidModel->GetEntropy();
		  h = e + P/rho;
		  c = FluidModel->GetSoundSpeed();
		  dkT = FluidModel->GetdktdT_rho();
		  dkrho = FluidModel->Getdktdrho_T();
		  dmuT = FluidModel->GetdmudT_rho();
		  dmurho = FluidModel->Getdmudrho_T();

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
			   << dkT <<'\t'
			   << dkrho<<'\t'
			   << dmuT <<'\t'
			   << dmurho <<'\n';
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

	su2double P, T, e, rho, s, cp, cv, h, mu, k, c, dkT, dkrho, dmuT, dmurho;
	double DR, DT;
	ofstream file;
	DT= (Tmax-Tmin)/(Tn-1);
	DR= (rhoMax-rhoMin)/(rhoN-1);
	cout << "Generating table: " << filename << '\n';
	file.open (filename);
	file << "rho\tT\tP\tmu\tk\tcp\th\ts\tc\te\tdkT\tdkrho\tdmuT\tdmurho\n";

	rho = rhoMax - DR;
	for (int i=0; i<rhoN; i++){
	   rho = rho + DR;
	   T = Tmin - DT;
	   for (int j=0; j<Tn; j++){
          T = T + DT;

		  FluidModel->SetTDState_rhoT(rho,T);
		  P = FluidModel->GetPressure();
		  mu = FluidModel->GetLaminarViscosity();
		  k = FluidModel->GetThermalConductivity();
		  cp = FluidModel->GetCp();
		  e = FluidModel->GetStaticEnergy();
		  s = FluidModel->GetEntropy();
		  c = FluidModel->GetSoundSpeed();
		  h = e + P/rho;
		  dkT = FluidModel->GetdktdT_rho();
		  dkrho = FluidModel->Getdktdrho_T();
		  dmuT = FluidModel->GetdmudT_rho();
		  dmurho = FluidModel->Getdmudrho_T();

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
			   << dkT <<'\t'
			   << dkrho<<'\t'
			   << dmuT <<'\t'
			   << dmurho<< '\n';
	   }
	}
	file.close();
}
