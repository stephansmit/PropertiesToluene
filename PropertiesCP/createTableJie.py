import numpy as np
import CoolProp.CoolProp as CP
import CoolProp.Plots as CPP
import matplotlib.pyplot as plt
import pandas as pd 

fluid = "Toluene"

print("Critical temperature: ", CP.PropsSI("Tcrit",fluid))
print("Critical pressure: ", CP.PropsSI("Pcrit",fluid))



df = pd.DataFrame()
df['T']=np.linspace(400,1000,601)
df['P']=1.8

print("Calculating Partial derivative of Enthalpy with respect to density at constant pressure")
df['dhdrho_P'  ]=df.apply(lambda x: CP.PropsSI("d(H)/d(D)|P","T", x['T'],"P", x['P']*1e5, fluid),axis=1)
print("Calculating Partial derivative of Enthalpy with respect to pressure at constant density")
df['dhdP_rho'  ]=df.apply(lambda x: CP.PropsSI("d(H)/d(P)|D","T", x['T'],"P", x['P']*1e5, fluid),axis=1)
print("Calculating Partial derivative of Entropy with respect to density at constant pressure")
df['dsdrho_P'  ]=df.apply(lambda x: CP.PropsSI("d(S)/d(D)|P","T", x['T'],"P", x['P']*1e5, fluid),axis=1)
print("Calculating Partial derivative of Entropy with respect to pressure at constant density")
df['dsdP_rho'  ]=df.apply(lambda x: CP.PropsSI("d(S)/d(P)|D","T", x['T'],"P", x['P']*1e5, fluid),axis=1)
print("Calculating Density")
df['rho']=df.apply(lambda x: CP.PropsSI("D", "T", x['T'], "P", x['P']*1e5, fluid),axis=1)
print("Calculating Laminar Viscosity")
df['mu' ]=df.apply(lambda x: CP.PropsSI("V", "T", x['T'], "P", x['P']*1e5, fluid),axis=1)
print("Calculating Thermal Conductivity")
df['k'  ]=df.apply(lambda x: CP.PropsSI("L", "T", x['T'], "P", x['P']*1e5, fluid),axis=1)
print("Calculating Thermal Heat Capacity")
df['cp' ]=df.apply(lambda x: CP.PropsSI("C", "T", x['T'], "P", x['P']*1e5, fluid),axis=1)
print("Calculating Entropy")
df['s'  ]=df.apply(lambda x: CP.PropsSI("S", "T", x['T'], "P", x['P']*1e5, fluid),axis=1)
print("Calculating Internal Energy")
df['e'  ]=df.apply(lambda x: CP.PropsSI("U", "T", x['T'], "P", x['P']*1e5, fluid),axis=1)
print("Calculating Speed of sound")
df['c'  ]=df.apply(lambda x: CP.PropsSI("A", "T", x['T'], "P", x['P']*1e5, fluid),axis=1)
print("Calculating Enthalpy")
df['h'  ]=df.apply(lambda x: CP.PropsSI("H", "T", x['T'], "P", x['P']*1e5, fluid),axis=1)


df.to_csv('../Tables/Toluene_PT_Jie.txt', sep='\t', float_format='%.6E', index=None)

