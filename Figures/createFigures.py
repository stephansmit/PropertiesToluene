import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.lines as mlines
import re
plt.rc('text', usetex=True)



def get_columns(name, columns):
    return filter(lambda x: re.match('^'+name, x) is not None, columns)

def get_columns_exceptCP(name, columns):
    return filter(lambda x: re.match('^'+name+'_PR|^'+name+'_IG', x) is not None, columns)

def plot_figure(grouped, columnname, ylabel, title, xlim, ylim, figure_name, plist, styles, logy):
    fig,ax = plt.subplots()
    for name,  group in grouped:
        style = styles[name]
        grouped.get_group(name).plot(x='T', y=columnname+'_CP',ax = ax, color='r', linestyle=style, logy=logy)
        grouped.get_group(name).plot(x='T', y=columnname+'_PR',ax = ax, color='b', linestyle=style, logy=logy)
        grouped.get_group(name).plot(x='T', y=columnname+'_IG',ax = ax, color='g', linestyle=style, logy=logy)
    
    ax.set_ylabel(ylabel)
    ax.set_xlabel('T [K]')
    ax.set_title(title)
    ax.set_xlim(xlim)
    ax.set_ylim(ylim)
    legend1 = plt.legend(['CoolProp', 'PR', 'IG'], loc=4)
    ax.add_artist(legend1)
    handles = [mlines.Line2D([], 
                             [], 
                             color='k',  
                             linestyle=value,
                             markersize=10, 
                             label='P='+str(name)) 
               for name, value in styles.iteritems()]
    handles_sorted = []
    handles_sorted.append(handles[2])
    handles_sorted.append(handles[1])
    handles_sorted.append(handles[0])
    handles_sorted.append(handles[3])
    legend2= plt.legend(handles=handles_sorted, loc=3)
    fig.savefig(figure_name)
    plt.close()


if __name__=="__main__":
    plist=[0.1, 5.0, 10.0, 15.0]
    styles = {0.1:'-',5: '-.',10: '--', 15:':'}
    
    df = pd.read_csv("../Tables/Toluene_PT.txt", sep='\t')

    for col in get_columns('k',df.columns):        df[col] = df[col]*1e3;
    for col in get_columns('mu',df.columns):       df[col] = df[col]*1e6;
    for col in get_columns('dsdP_rho',df.columns): df[col] = df[col]*1e3;
    for col in get_columns('dsdrho_P',df.columns): df[col] = df[col]/-1e3;
    for col in get_columns('dhdrho_P',df.columns): df[col] = df[col]/-1e3;


#    grouped = df[(df['P'].isin(plist))  & (df["rho_CP"]<300)  ].groupby("P")
    grouped = df[(df['P'].isin(plist))   ].groupby("P")
    print("creating figure thermal conductivity")
    plot_figure(grouped, 'k', 'k [kW /m K]', "Thermal conductivity with different models", [500,600], [25,45], "thermalconductivity.png", plist, styles, False)
    print("creating figure laminair viscosity")
    plot_figure(grouped, 'mu', r'$\displaystyle \mu [\mu Pa/ s]$',"Viscosity with different models", [500,600], [10,15], "viscosity.png", plist, styles,False)
    print("creating figure density")
    plot_figure(grouped, 'rho', r'$\displaystyle \rho [kg/m^3]$',"Density with different models", [500,600], [0,50], "density.png", plist, styles,False)
    print("creating figure speed of sound")
    plot_figure(grouped, 'c', 'c [m/s]',"Speed of sound with different models", [500,600], [150,240], "speedofsound.png", plist, styles,False)
    print("creating figure dsdrho_p")
    plot_figure(grouped, 'dsdrho_P', r'$\displaystyle -\frac{\partial s}{\partial \rho}|_P [-]$',
            "Parial derivative of entropy with respect to density at constant pressure", [500,600], [0.01,13], "dsdrho_p.png", plist, styles,True)
    print("creating figure dsdp_rho")
    plot_figure(grouped, 'dsdP_rho', r'$\displaystyle \frac{\partial s}{\partial P}|_\rho [-]$',
            "Parial derivative of entropy with respect to pressure at constant density", [500,600], [0.5,300],"dsdp_rho.png", plist, styles,True)
    print("creating figure dhdrho_P")
    plot_figure(grouped, 'dhdrho_P', r'$\displaystyle -\frac{\partial h}{\partial \rho}|_P [-]$',
            "Parial derivative of enthalpy with respect to density at constant pressure", [500,600], [1,7500], "dhdrho_p.png", plist, styles,True)
    print("creating figure dhdP_rho")
    plot_figure(grouped, 'dhdP_rho', r'$\displaystyle \frac{\partial h}{\partial P}|_\rho [-]$',
            "Parial derivative of enthalpy with respect to pressure at constant density", [500,600], [0.2,130],"dhdp_rho.png", plist, styles,True)



