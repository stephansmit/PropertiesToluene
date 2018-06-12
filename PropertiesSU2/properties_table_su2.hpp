
#pragma once

class CPropertiesTableSU2 {
protected:
		CFluidModel *FluidModel;

public:
		/*!
		 * \brief Constructor of the class.
		 */
		CPropertiesTableSU2(void);
		/*/
		 * \brief Destructor of the class.
		 */
		CPropertiesTableSU2(CFluidModel *FluidModel,
							CConductivityModel *ConductivityModel,
							CViscosityModel *ViscosityModel);

		void GenerateTable_PT(const char* filename,
												   su2double Pmax,
												   su2double Pmin,
												   int Pn,
												   su2double Tmax,
												   su2double Tmin,
												   int Tn );
		void GenerateTable_rhoT(const char* filename,
												   su2double rhoMax,
												   su2double rhoMin,
												   int rhoN,
												   su2double Tmax,
												   su2double Tmin,
												   int Tn );

		virtual ~CPropertiesTableSU2(void);

};

CPropertiesTableSU2::CPropertiesTableSU2(CFluidModel *FluidModel,
										 CConductivityModel *ConductivityModel,
										 CViscosityModel *ViscosityModel) {
  FluidModel->SetThermalConductivityModelDirect(ConductivityModel);
  FluidModel->SetLaminarViscosityModelDirect(ViscosityModel);
  this->FluidModel = FluidModel;
}

CPropertiesTableSU2::~CPropertiesTableSU2(void) {

}
