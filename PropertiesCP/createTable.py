import numpy as np
import CoolProp.CoolProp as CP
import CoolProp.Plots as CPP
import matplotlib.pyplot as plt
import pandas as pd 

fluid = "Toluene"

print("Critical temperature: ", CP.PropsSI("Tcrit",fluid))
print("Critical pressure: ", CP.PropsSI("Pcrit",fluid))


dfPR = pd.read_csv("../Tables/ToluenePR_PT.txt", sep='\t')
dfPR.columns = [str(col) + '_PR' for col in dfPR.columns]
dfIG = pd.read_csv("../Tables/TolueneIG_PT.txt", sep='\t')
dfIG.columns = [str(col) + '_IG' for col in dfIG.columns]
df = pd.concat([dfPR, dfIG], axis=1)
df['P']=df["P_PR"]
df['T']=df["T_IG"]
print("Calculating Density")
df['rho_CP']=df.apply(lambda x: CP.PropsSI("D", "T", x['T'], "P", x['P']*1e5, fluid),axis=1)
print("Calculating Laminar Viscosity")
df['mu_CP' ]=df.apply(lambda x: CP.PropsSI("V", "T", x['T'], "P", x['P']*1e5, fluid),axis=1)
print("Calculating Thermal Conductivity")
df['k_CP'  ]=df.apply(lambda x: CP.PropsSI("L", "T", x['T'], "P", x['P']*1e5, fluid),axis=1)
print("Calculating Thermal Heat Capacity")
df['cp_CP' ]=df.apply(lambda x: CP.PropsSI("C", "T", x['T'], "P", x['P']*1e5, fluid),axis=1)
print("Calculating Entropy")
df['s_CP'  ]=df.apply(lambda x: CP.PropsSI("S", "T", x['T'], "P", x['P']*1e5, fluid),axis=1)
print("Calculating Internal Energy")
df['e_CP'  ]=df.apply(lambda x: CP.PropsSI("U", "T", x['T'], "P", x['P']*1e5, fluid),axis=1)
print("Calculating Speed of sound")
df['c_CP'  ]=df.apply(lambda x: CP.PropsSI("A", "T", x['T'], "P", x['P']*1e5, fluid),axis=1)
print("Calculating Enthalpy")
df['h_CP'  ]=df.apply(lambda x: CP.PropsSI("H", "T", x['T'], "P", x['P']*1e5, fluid),axis=1)

df.to_csv('../Tables/Toluene_PT.txt', sep='\t', float_format='%.6E', index=None)

