// store material data
#include "database.h"
#include <cmath>
#include <iostream>

material* mdata[n_typ];

void creat_mdata()
{
	mdata[ACT] = new material[nACT+1];
	mdata[ELC] = new material[nELC+1];
	mdata[MEM] = new material[nMEM+1];
	mdata[SLN] = new material[nSLN+1];
	mdata[BND] = new material[nBND+1];
	mdata[FLM] = new material[nFLM+1];
}

void destroy_mdata()
{
	delete [] mdata[ACT];
	delete [] mdata[ELC];
	delete [] mdata[MEM];
	delete [] mdata[SLN];
	delete [] mdata[BND];
	delete [] mdata[FLM];
}

// database
void set_actm()	// active material
{
	mdata[ACT][MCMB].id_mat = MCMB;
	mdata[ACT][MCMB].id_typ = ACT;
	mdata[ACT][MCMB].id_rgn = ANODE;		// anode material
	mdata[ACT][MCMB].name = "MCMB";
	mdata[ACT][MCMB].grade = "Timcal";
	mdata[ACT][MCMB].density = 2.24e3;		// ?
	mdata[ACT][MCMB].Mw = M_C*6e-3;
	mdata[ACT][MCMB].cs_max = mdata[ACT][MCMB].density/mdata[ACT][MCMB].Mw;
	mdata[ACT][MCMB].cap_max = faraday/(mdata[ACT][MCMB].Mw*AhtoC);//372.25 mAh/g
	mdata[ACT][MCMB].cap_c = 371e0;
	mdata[ACT][MCMB].cap_d = 350e0;//355e0;
	mdata[ACT][MCMB].stoich(1e-6,0e0);//(0.00001e0, 0.00001e0);
	mdata[ACT][MCMB].U0 = 2e0;
	mdata[ACT][MCMB].U1 = 0e0;
	mdata[ACT][MCMB].rp = 9.0e-6;//6e-6;//10e-6;//XG modified on 08/10/2015 from ACB simulation
	mdata[ACT][MCMB].Vp = 4e0/3e0*pi*pow(mdata[ACT][MCMB].rp, 3);
	mdata[ACT][MCMB].afa = 0.5e0;
	mdata[ACT][MCMB].afc = 0.5e0;
	mdata[ACT][MCMB].cnd_elc = cnd_elc_MCMB;		// ??
	mdata[ACT][MCMB].dif_Li = dif_Li_MCMB_2; //2
	mdata[ACT][MCMB].ocp = ocp_MCMB_6;//5;
	mdata[ACT][MCMB].i0 = i0_MCMB_4;
	mdata[ACT][MCMB].dUdT = dUdT_MCMB_3;
	mdata[ACT][MCMB].dedt = dedt_MCMB;
	//Stress-related, added on 07/28/2015
	mdata[ACT][MCMB].pmv = 4.0815e-6; //m3/mol; J.E.S 162(2015) A1708-A1717
	mdata[ACT][MCMB].young_m=15e9; // Pa, J.Christensen, J. Solid State Electrochem. (2006), 293-319
	mdata[ACT][MCMB].poission=0.3; // J.Christensen, J. Solid State Electrochem. (2006), 293-319


	mdata[ACT][LTO].id_mat = LTO;
	mdata[ACT][LTO].id_typ = ACT;
	mdata[ACT][LTO].id_rgn = ANODE;
	mdata[ACT][LTO].name = "LTO";		// Li4Ti5O12
	mdata[ACT][LTO].grade = "AVG";
	mdata[ACT][LTO].density = 3.510e3;	// S. Stewart, J. Electrochem. Soc., 155, A253, 2008
	mdata[ACT][LTO].Mw = (M_Li*4e0/3e0 + M_Ti*5e0/3e0 + M_O*4e0)*1e-3;
	mdata[ACT][LTO].cs_max = mdata[ACT][LTO].density/mdata[ACT][LTO].Mw;
	mdata[ACT][LTO].cap_max = faraday/(mdata[ACT][LTO].Mw*AhtoC);
	mdata[ACT][LTO].cap_c = 170e0;
	mdata[ACT][LTO].cap_d = 170e0;
	mdata[ACT][LTO].stoich(0.01e0, 0.01e0);
	mdata[ACT][LTO].U0 = 2.5e0;
	mdata[ACT][LTO].U1 = 0e0;
	mdata[ACT][LTO].rp = 0.1e-6;			//  J. Christensen .etc, J Electrochem Soc, 153, A560 (2006).
	mdata[ACT][LTO].Vp = 4e0/3e0*pi*pow(mdata[ACT][LTO].rp, 3);
	mdata[ACT][LTO].afa = 0.5e0;
	mdata[ACT][LTO].afc = 0.5e0;
	mdata[ACT][LTO].cnd_elc = cnd_elc_LTO;
	mdata[ACT][LTO].dif_Li = dif_Li_LTO;
	mdata[ACT][LTO].ocp = ocp_LTO;
	mdata[ACT][LTO].i0 = i0_LTO;

	mdata[ACT][LCO].id_mat = LCO;
	mdata[ACT][LCO].id_typ = ACT;
	mdata[ACT][LCO].id_rgn = CATHODE;
	mdata[ACT][LCO].name = "LCO";		// LiCoO2
	mdata[ACT][LCO].grade = "AVG";
	mdata[ACT][LCO].density = 5.01e3;	// ?
	mdata[ACT][LCO].Mw = (M_Li + M_Co + M_O*2e0)*1e-3;
	mdata[ACT][LCO].cs_max = mdata[ACT][LCO].density/mdata[ACT][LCO].Mw;
	mdata[ACT][LCO].cap_max = faraday/(mdata[ACT][LCO].Mw*AhtoC);
	mdata[ACT][LCO].cap_c = 140e0;		// Wiki
	mdata[ACT][LCO].cap_d = 140e0;
	mdata[ACT][LCO].stoich(0.01e0, 0.01e0);
	mdata[ACT][LCO].U0 = 5e0;
	mdata[ACT][LCO].U1 = 2e0;
	mdata[ACT][LCO].rp = 3e-6;				// ??
	mdata[ACT][LCO].Vp = 4e0/3e0*pi*pow(mdata[ACT][LCO].rp, 3);
	mdata[ACT][LCO].afa = 0.5e0;
	mdata[ACT][LCO].afc = 0.5e0;
	mdata[ACT][LCO].cnd_elc = cnd_elc_LCO;
	mdata[ACT][LCO].dif_Li = dif_Li_LCO;
	mdata[ACT][LCO].ocp = ocp_LCO_2;
	mdata[ACT][LCO].i0 = i0_LCO; //i0_LFPO_1;
	mdata[ACT][LCO].dUdT = dUdT_LCO;
	//Stress-related, added on 07/28/2015, assumed the same as LCO
	mdata[ACT][LCO].pmv = mdata[ACT][LCO].Mw/mdata[ACT][LCO].density; 
	mdata[ACT][LCO].young_m=70e9; //Renganathan et al., J.E.S 157(2010), A155-163
	mdata[ACT][LCO].poission=0.16; //Renganathan et al., J.E.S 157(2010), A155-163

	mdata[ACT][LMO].id_mat = LMO;
	mdata[ACT][LMO].id_typ = ACT;
	mdata[ACT][LMO].id_rgn = CATHODE;
	mdata[ACT][LMO].name = "LMO";		// LiMn2O4
	mdata[ACT][LMO].grade = "AVG";
	mdata[ACT][LMO].density = 4.28e3;		// ?
	mdata[ACT][LMO].Mw = (M_Li + M_Mn*2e0 + M_O*4e0)*1e-3;
	mdata[ACT][LMO].cs_max = mdata[ACT][LMO].density/mdata[ACT][LMO].Mw;
	mdata[ACT][LMO].cap_max = faraday/(mdata[ACT][LMO].Mw*AhtoC);
	mdata[ACT][LMO].cap_c = 110e0;
	mdata[ACT][LMO].cap_d = 110e0;
	mdata[ACT][LMO].stoich(1e-2, 2e-2);//1e-5);
	mdata[ACT][LMO].U0 = 5e0;
	mdata[ACT][LMO].U1 = 3e0;
	mdata[ACT][LMO].rp = 4e-6;//4.15e-6;		// Targray
	mdata[ACT][LMO].Vp = 4e0/3e0*pi*pow(mdata[ACT][LMO].rp, 3);
	mdata[ACT][LMO].afa = 0.5e0;
	mdata[ACT][LMO].afc = 0.5e0;
	mdata[ACT][LMO].cnd_elc = cnd_elc_LMO_1;
	mdata[ACT][LMO].dif_Li = dif_Li_LMO_5;
	mdata[ACT][LMO].ocp = ocp_LMO_1; //LMO_2;
	mdata[ACT][LMO].i0 = i0_LMO_5;
	mdata[ACT][LMO].dUdT = dUdT_LMO;
	mdata[ACT][LMO].dedt = dedt_LMO;
	//Stress-related, added on 07/28/2015
	mdata[ACT][LMO].pmv = 3.497e-6; //m3/mol; X. Zhang, J.E.S 154(2007) A910-A916
	mdata[ACT][LMO].young_m=10e9; //Y. Dai, J. Power Source 247(2014) 365-376
	mdata[ACT][LMO].poission=0.3; //Y. Dai, J. Power Source 247(2014) 365-376

	mdata[ACT][NCM].id_mat = NCM;
	mdata[ACT][NCM].id_typ = ACT;
	mdata[ACT][NCM].id_rgn = CATHODE;
	mdata[ACT][NCM].name = "NCM";		// LiCo1/3Ni1/3Mn1/3O2
	mdata[ACT][NCM].grade = "AVG";
	mdata[ACT][NCM].density = 4.8e3;		// ?
	mdata[ACT][NCM].Mw = (M_Li+(M_Co+M_Ni+M_Mn)/3e0+M_O*2e0)*1e-3;
	mdata[ACT][NCM].cs_max = mdata[ACT][NCM].density/mdata[ACT][NCM].Mw;
	mdata[ACT][NCM].cap_max = faraday/(mdata[ACT][NCM].Mw*AhtoC);
	mdata[ACT][NCM].cap_c = 164e0;
	mdata[ACT][NCM].cap_d = 164e0;
	mdata[ACT][NCM].stoich(0.01e0, 0.05e0+0.06e0);
	mdata[ACT][NCM].U0 = 4.8e0;
	mdata[ACT][NCM].U1 = 0.0e0;
	mdata[ACT][NCM].rp = 3.0e-6; //5e-6;		// XG on 08/10/2015 based on ACB simulation
	mdata[ACT][NCM].Vp = 4e0/3e0*pi*pow(mdata[ACT][NCM].rp, 3);
	mdata[ACT][NCM].afa = 0.5e0;
	mdata[ACT][NCM].afc = 0.5e0;
	mdata[ACT][NCM].cnd_elc = cnd_elc_LNCM;
	mdata[ACT][NCM].dif_Li = dif_Li_LNCM_2;//2;
	mdata[ACT][NCM].ocp = ocp_LNCM_9;//6;//7;
	mdata[ACT][NCM].i0 = i0_LNCM;
	mdata[ACT][NCM].dUdT = dUdT_LNCM_2;	// unknown use LCO instead
	mdata[ACT][NCM].dedt = dedt_LNCM;
	//Stress-related, added on 07/28/2015, assumed the same as LMO
	mdata[ACT][NCM].pmv = 3.497e-6; //Assumed
	mdata[ACT][NCM].young_m=10e9; 
	mdata[ACT][NCM].poission=0.3; 

	mdata[ACT][LFP].id_mat = LFP;
	mdata[ACT][LFP].id_typ = ACT;
	mdata[ACT][LFP].id_rgn = CATHODE;
	mdata[ACT][LFP].name = "LFP";		// LiFePO4
	mdata[ACT][LFP].grade = "AVG";
	mdata[ACT][LFP].density = 3.6e3;		// K. Zaghib, Solid-State Lett., 8, A207 (2005)
	mdata[ACT][LFP].Mw = (M_Li + M_Fe + M_P + M_O*4e0)*1e-3;
	mdata[ACT][LFP].cs_max = mdata[ACT][LFP].density/mdata[ACT][LFP].Mw;
	mdata[ACT][LFP].cap_max = faraday/(mdata[ACT][LFP].Mw*AhtoC);
	mdata[ACT][LFP].cap_c = 160e0;
	mdata[ACT][LFP].cap_d = 160e0;
	mdata[ACT][LFP].stoich(0.01e0, 0.01e0);
	mdata[ACT][LFP].U0 = 4e0;
	mdata[ACT][LFP].U1 = 1e0;
	mdata[ACT][LFP].rp = 0.052e-6;
	mdata[ACT][LFP].Vp = 4e0/3e0*pi*pow(mdata[ACT][LFP].rp, 3);
	mdata[ACT][LFP].afa = 0.5e0;
	mdata[ACT][LFP].afc = 0.5e0;
	mdata[ACT][LFP].cnd_elc = cnd_elc_LFPO_1;
	mdata[ACT][LFP].dif_Li = dif_Li_LFPO_1;
	mdata[ACT][LFP].ocp = ocp_LFPO_1;
	mdata[ACT][LFP].i0 = i0_LFPO_2;
	mdata[ACT][LFP].dedt = dedt_LFP;

	mdata[ACT][LI].id_mat = LI;
	mdata[ACT][LI].id_typ = ACT;
	mdata[ACT][LI].id_rgn = ANODE;
	mdata[ACT][LI].name = "Li";
	mdata[ACT][LI].grade = "AVG";
	mdata[ACT][LI].density = 534e0;		// Wiki
	mdata[ACT][LI].Mw = M_Li*1e-3;
	mdata[ACT][LI].cs_max = mdata[ACT][LI].density/mdata[ACT][LI].Mw;
	mdata[ACT][LI].cap_max = faraday/(mdata[ACT][LI].Mw*AhtoC);
	mdata[ACT][LI].cap_c = mdata[ACT][LI].cap_max;
	mdata[ACT][LI].cap_d = mdata[ACT][LI].cap_max;
	mdata[ACT][LI].stoich(0e0, 0e0);
	mdata[ACT][LI].rp = 1e-5;
	mdata[ACT][LI].afa = 0.5e0;
	mdata[ACT][LI].afc = 0.5e0;
	mdata[ACT][LI].cnd_elc = cnd_elc_LI;
	mdata[ACT][LI].dif_Li = dif_Li_LI;
	mdata[ACT][LI].ocp = ocp_LI;
	mdata[ACT][LI].i0 = i0_LI;
	mdata[ACT][LI].dUdT = dUdT_LI;

	mdata[ACT][GRP2] = mdata[ACT][MCMB];
	mdata[ACT][GRP2].name = "GRP2";
	mdata[ACT][GRP2].rp = mdata[ACT][MCMB].rp/3;
	mdata[ACT][GRP3] = mdata[ACT][MCMB];
	mdata[ACT][GRP3].name = "GRP3";
	mdata[ACT][GRP3].rp = mdata[ACT][MCMB].rp/9;

	mdata[ACT][LFP2] = mdata[ACT][LFP];
	mdata[ACT][LFP2].name = "LFP2";
	mdata[ACT][LFP2].rp = mdata[ACT][LFP].rp/3;
	mdata[ACT][LFP3] = mdata[ACT][LFP];
	mdata[ACT][LFP3].name = "LFP3";
	mdata[ACT][LFP3].rp = mdata[ACT][LFP].rp*3;

	mdata[ACT][LMO2] = mdata[ACT][LMO];
	mdata[ACT][LMO2].name = "LMO2";
	mdata[ACT][LMO2].rp = mdata[ACT][LMO].rp/3;
	mdata[ACT][LMO3] = mdata[ACT][LMO];
	mdata[ACT][LMO3].name = "LMO3";
	mdata[ACT][LMO3].rp = mdata[ACT][LMO].rp*3;

	mdata[ACT][NCM2] = mdata[ACT][NCM];
	mdata[ACT][NCM2].name = "NCM2";
	mdata[ACT][NCM2].rp = mdata[ACT][NCM].rp/3;
	mdata[ACT][NCM3] = mdata[ACT][NCM];
	mdata[ACT][NCM3].name = "NCM3";
	mdata[ACT][NCM3].rp = mdata[ACT][NCM].rp/9;

	mdata[ACT][NCM622].id_mat = NCM622;
	mdata[ACT][NCM622].id_typ = ACT;
	mdata[ACT][NCM622].id_rgn = CATHODE;
	mdata[ACT][NCM622].name = "NCM622";		// LiNi(0.6)Co(0.2)Mn(0.2)O2
	mdata[ACT][NCM622].grade = "AVG";
	mdata[ACT][NCM622].density = 4.8e3;//mdata[ACT][NCM].density;		// ?
	mdata[ACT][NCM622].Mw = (M_Li+M_Ni*0.6+M_Mn*0.2+M_Co*0.2+M_O*2.0)*1.0e-3;//mdata[ACT][NCM].Mw;
	mdata[ACT][NCM622].cs_max = mdata[ACT][NCM622].density/mdata[ACT][NCM622].Mw; //mdata[ACT][NCM].cs_max; //mdata[ACT][NCM622].density/mdata[ACT][NCM622].Mw;
	mdata[ACT][NCM622].cap_max = faraday/(mdata[ACT][NCM622].Mw*AhtoC); // mdata[ACT][NCM].cap_max;//faraday/(mdata[ACT][NCM622].Mw*AhtoC);
	mdata[ACT][NCM622].cap_c = 190e0;//mdata[ACT][NCM].cap_c;//190e0;
	mdata[ACT][NCM622].cap_d = 182e0;//mdata[ACT][NCM].cap_d;//180e0;
	mdata[ACT][NCM622].stoich(0.001e0, 0.12e0);//0.05e0+0.01 +0.01);
	mdata[ACT][NCM622].U0 = 4.8e0;
	mdata[ACT][NCM622].U1 = 3.0e0;
	mdata[ACT][NCM622].rp = 5.0e-6; //2.5e-6;		
	mdata[ACT][NCM622].Vp = 4e0/3e0*pi*pow(mdata[ACT][NCM622].rp, 3);//mdata[ACT][NCM].Vp; //4e0/3e0*pi*pow(mdata[ACT][NCM622].rp, 3);
	mdata[ACT][NCM622].afa = 0.5e0;
	mdata[ACT][NCM622].afc = 0.5e0;
	mdata[ACT][NCM622].cnd_elc = cnd_elc_LNCM622;
	mdata[ACT][NCM622].dif_Li = dif_Li_LNCM622_1;
	mdata[ACT][NCM622].ocp = ocp_LNCM622_1;
	mdata[ACT][NCM622].i0 = i0_LNCM622_1; //  i0_LNCM622_1;//mdata[ACT][NCM].i0; 
	mdata[ACT][NCM622].dUdT = dUdT_LNCM_2;	// unknown use LCO instead
	mdata[ACT][NCM622].dedt = dedt_LNCM;
	//Stress-related, added on 07/28/2015, assumed the same as LMO
	mdata[ACT][NCM622].pmv = 3.497e-6; //Assumed
	mdata[ACT][NCM622].young_m=10e9; 
	mdata[ACT][NCM622].poission=0.3; 
}

void set_film()
{
	mdata[FLM][FGR].id_mat = FGR;
	mdata[FLM][FGR].id_typ = FLM;
	mdata[FLM][FGR].id_rgn = ANODE;
	mdata[FLM][FGR].name = "Graphite SEI";
	mdata[FLM][FGR].grade = "AVG";
	mdata[FLM][FGR].density = 1.690e3;
	mdata[FLM][FGR].Mw = 162e-3;
	mdata[FLM][FGR].cap_max = faraday/(mdata[FLM][FGR].Mw*AhtoC);
	mdata[FLM][FGR].cap_c = mdata[FLM][FGR].cap_max;
	mdata[FLM][FGR].cap_d = mdata[FLM][FGR].cap_max;
	mdata[FLM][FGR].ls0 = 5e-9;
	mdata[FLM][FGR].lsin = 50e-9;
	mdata[FLM][FGR].porosity = 0.05e0;
	mdata[FLM][FGR].cnd_ion = cnd_ion_FGR;
	mdata[FLM][FGR].i0 = i0_FGR;
	mdata[FLM][FGR].k0 = k0_FGR;//This value is used
	mdata[FLM][FGR].n_ele = 1.0;
	//mdata[FLM][FGR].C1 = -1e-11;

	mdata[FLM][FNCM].id_mat = FNCM;
	mdata[FLM][FNCM].id_typ = FLM;
	mdata[FLM][FNCM].id_rgn = CATHODE;
	mdata[FLM][FNCM].name = "NCM film";
	mdata[FLM][FNCM].grade = "AVG";
	mdata[FLM][FNCM].density = 1.690e3;
	mdata[FLM][FNCM].Mw = 162e-3;// + 207e-3;
	mdata[FLM][FNCM].cap_max = faraday/(mdata[FLM][FNCM].Mw*AhtoC);
	mdata[FLM][FNCM].cap_c = mdata[FLM][FNCM].cap_max;
	mdata[FLM][FNCM].cap_d = mdata[FLM][FNCM].cap_max;
	mdata[FLM][FNCM].ls0 = 2e-9;
	mdata[FLM][FNCM].lsin = 2e-9;
	mdata[FLM][FNCM].porosity = 0.05e0;//0.01e0*4*0.56*0.86;//0.397;//0.05e0;
	mdata[FLM][FNCM].cnd_ion = cnd_ion_FNCM;
	mdata[FLM][FNCM].i0 = i0_FNCM;
	mdata[FLM][FNCM].k0 = k0_FNCM;
	//mdata[FLM][FNCM].C1 = -1e-11;

	mdata[FLM][FLMO].id_mat = FLMO;
	mdata[FLM][FLMO].id_typ = FLM;
	mdata[FLM][FLMO].id_rgn = CATHODE;
	mdata[FLM][FLMO].name = "LMO film";
	mdata[FLM][FLMO].grade = "AVG";
	mdata[FLM][FLMO].density = 1.690e3;
	mdata[FLM][FLMO].Mw = 162e-3;// + 207e-3;
	mdata[FLM][FLMO].cap_max = faraday/(mdata[FLM][FLMO].Mw*AhtoC);
	mdata[FLM][FLMO].cap_c = mdata[FLM][FLMO].cap_max;
	mdata[FLM][FLMO].cap_d = mdata[FLM][FLMO].cap_max;
	mdata[FLM][FLMO].ls0 = 0;//2e-9;
	mdata[FLM][FLMO].lsin = 0;//2e-9;
	mdata[FLM][FLMO].porosity = 0.01e0*4*0.56*0.86;//0.397;//0.05e0;
	mdata[FLM][FLMO].cnd_ion = cnd_ion_FLMO;
	mdata[FLM][FLMO].i0 = i0_FLMO;
	mdata[FLM][FLMO].k0 = k0_FLMO;
}

void set_elcm() // electronic conductive material
{
	mdata[ELC][CU].id_mat = CU;
	mdata[ELC][CU].id_typ = ELC;
	mdata[ELC][CU].id_rgn = ANODE;
	mdata[ELC][CU].name = "Cu";
	mdata[ELC][CU].grade = "AVG";
	mdata[ELC][CU].density = 8.94e3;
	mdata[ELC][CU].cnd_elc = cnd_elc_CU;

	mdata[ELC][AL].id_mat = AL;
	mdata[ELC][AL].id_typ = ELC;
	mdata[ELC][AL].id_rgn = CATHODE;
	mdata[ELC][AL].name = "Al";
	mdata[ELC][AL].grade = "AVG";
	mdata[ELC][AL].density = 2.70e3;
	mdata[ELC][AL].cnd_elc = cnd_elc_AL;

	mdata[ELC][CARBON].id_mat = CARBON;
	mdata[ELC][CARBON].id_typ = ELC;
	mdata[ELC][CARBON].id_rgn = rgn0;	// anode or cathode
	mdata[ELC][CARBON].name = "Carbon";
	mdata[ELC][CARBON].grade = "Super-P";
	mdata[ELC][CARBON].density = 1.95e3;
}

void set_memm()	// membrane material
{
	mdata[MEM][PE].id_mat = PE;
	mdata[MEM][PE].id_typ = MEM;
	mdata[MEM][PE].id_rgn = SEPARATOR;
	mdata[MEM][PE].name = "PE";
	mdata[MEM][PE].grade = "PE1120";		// targray
	mdata[MEM][PE].density = 920e0;			// wiki roughly
	mdata[MEM][PE].porosity = 0.46e0;		// targray
	mdata[MEM][PE].thickness = 20e-6;		// targray

	mdata[MEM][PP].id_mat = PP;
	mdata[MEM][PP].id_typ = MEM;
	mdata[MEM][PP].id_rgn = SEPARATOR;
	mdata[MEM][PP].name = "PP";
	mdata[MEM][PP].grade = "AVG";
	mdata[MEM][PP].density = 855e0;			// wiki
	mdata[MEM][PP].porosity = 0.40e0;		// targray
	mdata[MEM][PP].thickness = 25e-6;		// targray
}

void set_slnm()		// solution
{
	mdata[SLN][sln1].id_mat = sln1;
	mdata[SLN][sln1].id_typ = SLN;
	mdata[SLN][sln1].id_rgn = ELECTROLYTE;
	mdata[SLN][sln1].name = "LiPF6-EC1/3-DMC2/3";
	mdata[SLN][sln1].grade = "AVG";
	mdata[SLN][sln1].density = 0.9e3;		// ??
	mdata[SLN][sln1].tplus = 0.38e0;		// L Valoen & J Reimers, J. Electrochem. Soc., 152, A882, 2005 
	mdata[SLN][sln1].cnd_ion = cnd_ion_sln1;
	mdata[SLN][sln1].dif_Li = dif_Li_sln1;
	mdata[SLN][sln1].dlnfdlnc = dlnfdlnc_sln1;

	mdata[SLN][sln2].id_mat = sln2;
	mdata[SLN][sln2].id_typ = SLN;
	mdata[SLN][sln2].id_rgn = ELECTROLYTE;
	mdata[SLN][sln2].name = "LiPF6-PC10%-EC27%-DMC63%";
	mdata[SLN][sln2].grade = "AVG";
	mdata[SLN][sln2].density = 1.2e3;//0.9e3;		// ??
	mdata[SLN][sln2].tplus = 0.38e0;		// L Valoen & J Reimers, J. Electrochem. Soc., 152, A882, 2005 
	mdata[SLN][sln2].cnd_ion = cnd_ion_sln2;//_R2;based on experience, using activation energy approach does not have big influence
	mdata[SLN][sln2].dif_Li = dif_Li_sln2;
	mdata[SLN][sln2].dlnfdlnc = dlnfdlnc_sln2;
	mdata[SLN][sln2].dif_EC = dif_EC_sln2;
}

void set_bndm()		// binder material
{
	mdata[BND][PVDF].id_mat = PVDF;
	mdata[BND][PVDF].id_typ = BND;
	mdata[BND][PVDF].name = "PVDF";				// Polyvinylidene Fluoride
	mdata[BND][PVDF].grade = "AVG";
	mdata[BND][PVDF].density = 1.78e3;		// Wiki

	mdata[BND][SBR].id_mat = SBR;
	mdata[BND][SBR].id_typ = BND;
	mdata[BND][SBR].name = "SBR";					// Styrene Butadiene Rubber
  mdata[BND][SBR].density=0.85e3;		//pseudo-density of SBR-CMC mixture with SBR:CMC mass ratio of 2.2:1.4; fitted to BMW electrode
 //mdata[BND][SBR].density = 1.52e3;		//website-http://www.mtixtl.com/Styrene-ButadieneRubberSBRbinderforLi-ionBatteryAnode260g/bottle.aspx
}

void set_addm()		// additive material
{
}

void set_mdata()		// set all materials
{
	set_actm();
	set_film();
	set_elcm();
	set_memm();
	set_slnm();
	//set_sltm();
	//set_svtm();
	set_bndm();
	set_addm();
}

// material ocp functions

double ocp_LI(double x, double T, int is)
{
	return 0e0;
}

double ocp_MCMB_1(double x, double T, int is)
{	
	// M. Guo .etc, J. Electrochem. Soc., 158, A122, 2011
	// for 0<=x<=0.8
	double U, U0, U1, U2, U3, U4, U5;
	if(x>=0e0&&x<=0.8e0)
	{
		U0 = 0.13966e0;
		U1 = 0.68920e0*exp(-49.20361e0*x);
		U2 = 0.41903e0*exp(-254.40067e0*x);
		U3 = -exp(49.97886e0*x - 43.37888e0);
		U4 = -0.028221e0*atan(22.52300e0*x - 3.65328e0);
		U5 = -0.01308e0*atan(28.34801e0*x - 13.43960e0);
		U = U0 + U1 + U2 + U3 + U4 + U5;
	}
	else if(x>0.8e0&&x<=1e0)
	{
		U = ocp_MCMB_1(0.8e0, T, is);
		U = U + (mdata[ACT][MCMB].U1 - U)*(x-0.8e0)/0.2e0;
	}
	else
	{
		std::cout<<"Anode Stoich out of range!"<<std::endl;
		exit(0);
	}
	return U;
}

double ocp_MCMB_2(double x, double T, int is)
{
	// J. Christensen .etc, J. Electrochem. Soc., 153, A560, 2006
	double U;
	U = 0.124e0 + 1.5e0*exp(-70e0*x) + 0.0155e0*tanh((x-0.105e0)/0.029e0)
		- 0.011e0*tanh((x-0.124e0)/0.0226e0) - 0.102e0*tanh((x-0.194)/0.142e0)
		- 0.0351e0*tanh((x-0.286e0)/0.083e0) - 0.0147e0*tanh((x-0.5e0)/0.034e0)
		- 0.0045e0*tanh((x-0.9e0)/0.119e0) - 0.0022e0*tanh((x-0.98e0)/0.0164e0)
		- 0.035e0*tanh((x-0.99e0)/0.05e0);
	return U;
}

double ocp_MCMB_3(double x, double T, int is)
{
	// P. Arora .etc, J. Electrochem. Soc., 146, 3543, 1999
	double U;
	double xmin = 0.01e0;
	double xmax = 1e0;
	if(x>=xmin && x<=xmax)
	{
		U = 0.7222e0 + 0.13868e0*x + 0.028952e0*sqrt(x) - 0.017189e0/x
		+ 0.0019144e0/(x*sqrt(x)) + 0.28082e0*exp(15e0*(0.06e0 - x))
		- 0.79844e0*exp(0.44649e0*(x - 0.92e0));
	}
	else if(x>=0e0 && x<xmin)
	{
		U = ocp_MCMB_3(xmin, T, is);
		U = U + (mdata[ACT][MCMB].U0 - U)*(xmin - x)/xmin;
	}
	else if(x>xmax && x<=1e0)
	{
		U = ocp_MCMB_3(xmax, T, is);
		U = U + (mdata[ACT][MCMB].U1 - U)*(x - xmax)/(1e0 - xmax);
	}
	else
	{
		std::cout<<"Anode Stoich out of range!"<<std::endl;
		exit(0);
	}
	return U;
}

double ocp_MCMB_4(double xsoc, double T, int is)
{
	// Fang's code
	double ocpA_;
    int i;
    double t1,t2,o1,o2;

    const double thetaa[51]=
    {
        0.000000e+000,
        2.000000e-002, 4.000000e-002, 6.000000e-002, 8.000000e-002, 1.000000e-001,
        1.200000e-001, 1.400000e-001, 1.600000e-001, 1.800000e-001, 2.000000e-001,
        2.200000e-001, 2.400000e-001, 2.600000e-001, 2.800000e-001, 3.000000e-001,
        3.200000e-001, 3.400000e-001, 3.600000e-001, 3.800000e-001, 4.000000e-001,
        4.200000e-001, 4.400000e-001, 4.600000e-001, 4.800000e-001, 5.000000e-001,
        5.200000e-001, 5.400000e-001, 5.600000e-001, 5.800000e-001, 6.000000e-001,
        6.200000e-001, 6.400000e-001, 6.600000e-001, 6.800000e-001, 7.000000e-001,
        7.200000e-001, 7.400000e-001, 7.600000e-001, 7.800000e-001, 8.000000e-001,
        8.200000e-001, 8.400000e-001, 8.600000e-001, 8.800000e-001, 9.000000e-001,
        9.200000e-001, 9.400000e-001, 9.600000e-001, 9.800000e-001, 1.000000e+000
    };

    const double ocpa0[51]=
    {
        8.023320e-001,
        6.976394e-001, 5.899001e-001, 4.443452e-001, 3.525619e-001, 3.045605e-001,
        2.812786e-001, 2.673829e-001, 2.567842e-001, 2.463399e-001, 2.350252e-001,
        2.249257e-001, 2.219204e-001, 2.110007e-001, 2.053662e-001, 2.011380e-001,
        1.916447e-001, 1.886998e-001, 1.886998e-001, 1.843819e-001, 1.775884e-001,
        1.745222e-001, 1.714559e-001, 1.683897e-001, 1.665527e-001, 1.665527e-001,
        1.665527e-001, 1.665527e-001, 1.665527e-001, 1.665527e-001, 1.648705e-001,
        1.631605e-001, 1.614505e-001, 1.585595e-001, 1.552290e-001, 1.513629e-001,
        1.463134e-001, 1.405766e-001, 1.388689e-001, 1.388689e-001, 1.388689e-001,
        1.385141e-001, 1.368675e-001, 1.352208e-001, 1.335741e-001, 1.333321e-001,
        1.333321e-001, 1.333321e-001, 1.333321e-001, 1.309082e-001, 1.056482e-001
    };

    if(xsoc<0e0) xsoc=1.e-8;
	  if(xsoc>1e0) xsoc=1e0-1.e-8;

    i=0;
    while(xsoc>thetaa[i]) i++;

    t1=thetaa[i];
    t2=thetaa[i-1];
    o1=ocpa0[i];
    o2=ocpa0[i-1];
    ocpA_=(o1-o2)/(t1-t2)*(xsoc-t1)+o1;

    return ocpA_;
}

double ocp_MCMB_5(double x, double T, int is)
{
	// M. Verbrugge, J. Electrochem. Soc., 150, A374, 2003
	int icount = 0;
	int nmid;
	int nmin = 0;
	int nmax = sizeof(x_MCMB_5)/sizeof(double) - 1;
	double U;
	const double xmin = x_MCMB_5[nmin];
	const double xmax = x_MCMB_5[nmax];
	//if(x>=0e0 && x<=0.026e0)		// Use part of MCMB1 data for x<=0.026
	//{
	//	U = 0.13966e0 + 0.68920e0*exp(-49.20361e0*x) + 0.41903e0*exp(-254.40067e0*x)
	//		-exp(49.97886e0*x - 43.37888e0) + -0.028221e0*atan(22.52300e0*x - 3.65328e0)
	//		-0.01308e0*atan(28.34801e0*x - 13.43960e0);
	//	return U;
	//}
	if(x>=xmin && x<=xmax)
	{
		while(nmax - nmin>1)
		{
			nmid = (nmin + nmax)/2;
			if(x>x_MCMB_5[nmid] && x<x_MCMB_5[nmax]) nmin = nmid;
			else if(x>x_MCMB_5[nmin] && x<x_MCMB_5[nmid]) nmax = nmid;
			else if(x==x_MCMB_5[nmin]) return y_MCMB_5[nmin];
			else if(x==x_MCMB_5[nmid]) return y_MCMB_5[nmid];
			else if(x==x_MCMB_5[nmax]) return y_MCMB_5[nmax];
			icount ++;
		}
		U = y_MCMB_5[nmin] + (x - x_MCMB_5[nmin])/(x_MCMB_5[nmax] - x_MCMB_5[nmin])
			*(y_MCMB_5[nmax] - y_MCMB_5[nmin]);
		//std::cout<<x<<" "<<icount<<std::endl;
		return U;
	}
	else if(x>=0e0 && x<xmin)
	{
		U = ocp_MCMB_5(xmin, T, is);
		U = U + (mdata[ACT][MCMB].U0 - U)*(xmin - x)/xmin;
	}
	else if(x>xmax && x<=1e0)
	{
		U = ocp_MCMB_5(xmax, T, is);
		U = U + (mdata[ACT][MCMB].U1 - U)*(x - xmax)/(1e0 - xmax);
	}
	else if(x>1e0)
		U = mdata[ACT][MCMB].U1;
	else if(x<0e0)
		U = mdata[ACT][MCMB].U0;
	else
	{
		std::cout<<mdata[ACT][MCMB].name<<" Stoich "<<x<<" out of range!"<<std::endl;
		exit(0);
	}
	return U;
}

double ocp_MCMB_6(double x, double T, int is)
{
	// Use fitting equation for data in M. Verbrugge, J. Electrochem. Soc., 150, A374, 2003
	double U;
	double U0, U1, U2, U3, U4, U5;
	const double xmin = 2e-5;
	const double xmax = 0.999e0;

	if(x>=xmin && x<=xmax)
	{
		U0 = 0.1493e0;
		U1 = 0.8493e0*exp(-61.79e0*x);
		U2 = 0.3824e0*exp(-665.8e0*x);
		U3 = -exp(39.42e0*x - 41.92e0);
		U4 = -0.03131e0*atan(25.59e0*x - 4.099e0);
		U5 = -0.009434e0*atan(32.49e0*x - 15.74e0);
		U = U0 + U1 + U2 + U3 + U4 + U5;
		return U;
	}
	else if(x>=0e0 && x<xmin)
	{
		U = ocp_MCMB_6(xmin, T, is);
		U = U + (mdata[ACT][MCMB].U0 - U)*(xmin - x)/xmin;
	}
	else if(x>xmax && x<=1e0)
	{
		U = ocp_MCMB_6(xmax, T, is);
		U = U + (mdata[ACT][MCMB].U1 - U)*(x - xmax)/(1e0 - xmax);
	}
	else if(x>1e0)
	{
		std::cout<<"Anode Stoich "<<x<<" out of range*****!"<<"\t"<<"ncyc="<<C1.nc<<"\t"<<"Voltage = "<<C1.voltage<<"\t"<<"Current = "<<C1.I<<std::endl;
		exit(0);
		//U = 0e0;
	}
	else
	{
		std::cout<<"Anode Stoich "<<x<<" out of range!***"<<"\t"<<"ncyc="<<C1.nc<<"Voltage = "<<C1.voltage<<"\t"<<"Current = "<<C1.I<<"\t"<<"ntc = "<<ntc<<"\t"<<"ntd = "<<ntd<<std::endl;
		exit(0);
	}
	return U;
}

double ocp_LTO(double x, double T, int is)
{
	// S. Stewart, J. Electrochem. Soc., 155, A253, 2008
	double U;
	double xmin = 0e0;
	double xmax = 0.995e0;
	if(x>=xmin && x<=xmax)
	{
		U = 2.73577e0 - 1.55862e0*x + 0.773926e0*exp(-24.5394e0*x)
			+ (1.15846e0 - 1.53876e0*x)*tanh(26.4455e0*(x - 1.00134e0));
	}
	else if(x>=0e0 && x<xmin)
	{
		U = ocp_LTO(xmin, T, is);
		U = U + (mdata[ACT][LTO].U0 - U)*(xmin - x)/xmin;
	}
	else if(x>xmax && x<=1e0)
	{
		U = ocp_LTO(xmax, T, is);
		U = U + (mdata[ACT][LTO].U1 - U)*(x - xmax)/(1e0 - xmax);
	}
	else if(x>1e0)
	{
		U = mdata[ACT][LTO].U1;
	}
	else
	{
		//std::cout<<"Anode Stoich out of range!"<<std::endl;
		std::cout<<mdata[ACT][LTO].name<<" Stoich "<<x<<" out of range!"<<std::endl;
		exit(0);
	}
	return U;
}

double ocp_LCO_1(double x, double T, int is)
{
	// M. Guo .etc, J. Electrochem. Soc., 158, A122, 2011
	double U;
	double xmin = 0.46e0;
	double xmax = 1e0;
	if(x>=xmin && x<=xmax)
	{
		U = 4.04596e0 + exp(-42.30027e0*x + 16.56714e0) -0.04880e0*atan(50.01833e0*x - 26.48897e0)
			-0.05447*atan(18.99678e0*x - 12.32362e0) -exp(78.24095e0*x - 78.68074e0);
	}
	else if(x>=0e0 && x<xmin)
	{
		U = ocp_LCO_1(xmin, T, is);
		U = U + (mdata[ACT][LCO].U0 - U)*(xmin - x)/xmin;
	}
	else if(x>xmax && x<=1e0)
	{
		U = ocp_LCO_1(xmax, T, is);
		U = U + (mdata[ACT][LCO].U1 - U)*(x - xmax)/(1e0 - xmax);
	}
	else
	{
		std::cout<<"Cathode Stoich out of range!"<<std::endl;
		exit(0);
	}
	return U;
}

double ocp_LCO_2(double x, double T, int is)
{
	// M. Tang .etc, J. Electrochem. Soc., 156, A390, 2009
	double U;
	double xmin = 0.42e0;
	double xmax = 1e0;
	if(x>=xmin && x<=xmax)
	{
		double y = 1e0 - x;
		double y2 = y*y;
		double y3 = y2*y;
		double y4 = y3*y;
		double y5 = y4*y;
		U = 3.85516954e0 + 1.247319422e0*y - 11.15240126e0*y2 + 42.8184855e0*y3
			- 67.71099749e0*y4 + 42.50815332e0*y5 - 6.13244713e-4*exp(7.657419995e0*pow(x,115));
	}
	else if(x>=0e0 && x<xmin)
	{
		U = ocp_LCO_2(xmin, T, is);
		U = U + (mdata[ACT][LCO].U0 - U)*(xmin - x)/xmin;
	}
	else if(x>xmax && x<=1e0)
	{
		U = ocp_LCO_2(xmax, T, is);
		U = U + (mdata[ACT][LCO].U1 - U)*(x - xmax)/(1e0 - xmax);
	}
	else
	{
		std::cout<<"Cathode Stoich out of range!"<<std::endl;
		exit(0);
	}
	return U;
}

double ocp_LMO_1(double x, double T, int is)
{
	// M. Doyle, John Newman, J. Electrochem. Soc., 143, 1890, 1996
	double U;
	double xmin = 0.17e0;
	double xmax = 0.998432e0;
	if(x>=xmin && x<=xmax)
	{
		U = 4.19829e0 + 0.0565661e0*tanh(-14.5546e0*x + 8.60942e0) + 
			-0.0275479e0*(1e0/pow(0.998432e0-x, 0.492465) - 1.90111)
			-0.157123e0*exp(-0.04738*x) + 0.810239e0*exp(-40e0*(x-0.133875));
	}
	else if(x>=0e0 && x<xmin)
	{
		U = ocp_LMO_1(xmin, T, is);
		U = U + (mdata[ACT][LMO].U0 - U)*(xmin - x)/xmin;
	}
	else if(x>xmax && x<=1e0)
	{
		U = ocp_LMO_1(xmax, T, is);
		U = U + (mdata[ACT][LMO].U1 - U)*(x - xmax)/(1e0 - xmax);
	}
	else
	{
		std::cout<<"Cathode Stoich out of range!"<<std::endl;
		exit(0);
	}
	return U;
}

double ocp_LMO_2(double x, double T, int is)
{
	// K. Thomas .etc, J. Electrochem. Soc., 148, A570, 2001
	double U;
	double xmin = 0.17e0;
	double xmax = 1e0;
	if(x>=xmin && x<=xmax)
	{
		U = 4.16643e0 + 0.04688e0*tanh(-18.12e0*x + 10.5e0) - 0.01176e0*pow(1.108e0 - x, -1.39e0)
			- 0.06627e0*exp(-0.899e0*pow(x + 0.051e0, 28)) + 0.0037e0*exp(7.8e0 - 26.8e0*x)
			+ 0.009e0*exp(36e0 - 200e0*x) - 0.0016e0*exp(386e0*x - 381e0);
	}
	else if(x>=0e0 && x<xmin)
	{
		U = ocp_LMO_2(xmin, T, is);
		U = U + (mdata[ACT][LMO].U0 - U)*(xmin - x)/xmin;
	}
	else if(x>xmax && x<=1e0)
	{
		U = ocp_LMO_2(xmax, T, is);
		U = U + (mdata[ACT][LMO].U1 - U)*(x - xmax)/(1e0 - xmax);
	}
	else
	{
		std::cout<<"Cathode Stoich out of range!"<<std::endl;
		exit(0);
	}
	return U;
}

double ocp_LNCM_1(double x, double T, int is)
{
	// S. Stewart .etc, J. Electrochem. Soc., 155, A664, 2008
	double U;
	double xmin = 0.387e0;
	double xmax = 1e0;
	if(x>=xmin && x<=xmax)
	{
		U = 6.0826e0 - 6.9922e0*x + 7.1062e0*x*x 
			- 0.54549e-4*exp(124.23e0*x - 114.2593e0) - 2.5947e0*x*x*x;
	}
	else if(x>=0e0 && x<xmin)
	{
		U = ocp_LNCM_1(xmin, T, is);
		U = U + (mdata[ACT][NCM].U0 - U)*(xmin - x)/xmin;
	}
	else if(x>xmax && x<=1e0)
	{
		U = ocp_LNCM_1(xmax, T, is);
		U = U + (mdata[ACT][NCM].U1 - U)*(x - xmax)/(1e0 - xmax);
	}
	else
	{
		std::cout<<"Cathode Stoich out of range!"<<std::endl;
		exit(0);
	}
	return U;
}

double ocp_LNCM_2(double x, double T, int is)
{
	// N. Yabuuchi, J. Electrochem. Soc., 154, A314, 2007
	int icount = 0;
	int nmid;
	int nmin = 0;
	int nmax = sizeof(x_LNCM_2)/sizeof(double) - 1;
	double U;
	const double xmin = x_LNCM_2[nmin];
	const double xmax = x_LNCM_2[nmax];
	if(x>=xmin && x<=xmax)
	{
		
		while(nmax - nmin>1)
		{
			nmid = (nmin + nmax)/2;
			if(x>x_LNCM_2[nmid] && x<x_LNCM_2[nmax]) nmin = nmid;
			else if(x>x_LNCM_2[nmin] && x<x_LNCM_2[nmid]) nmax = nmid;
			else if(x==x_LNCM_2[nmin]) return y_LNCM_2[nmin];
			else if(x==x_LNCM_2[nmid]) return y_LNCM_2[nmid];
			else if(x==x_LNCM_2[nmax]) return y_LNCM_2[nmax];
			icount ++;
		}
		U = y_LNCM_2[nmin] + (x - x_LNCM_2[nmin])/(x_LNCM_2[nmax] - x_LNCM_2[nmin])
			*(y_LNCM_2[nmax] - y_LNCM_2[nmin]);
		//std::cout<<x<<" "<<icount<<std::endl;
		return U;
	}
	else if(x>=0e0 && x<xmin)
	{
		U = ocp_LNCM_2(xmin, T, is);
		U = U + (mdata[ACT][NCM].U0 - U)*(xmin - x)/xmin;
	}
	else if(x>xmax && x<=1e0)
	{
		U = ocp_LNCM_2(xmax, T, is);
		U = U + (mdata[ACT][NCM].U1 - U)*(x - xmax)/(1e0 - xmax);
	}
	else
	{
		std::cout<<"Cathode Stoich out of range!"<<std::endl;
		exit(0);
	}
	return U;
}

double ocp_LNCM_3(double x, double T, int is)
{
	// Z. Li, J. Electrochem. Soc., 158, A516, 2011
	// Discharge from 4.3V
	int icount = 0;
	int nmid;
	int nmin = 0;
	int nmax = sizeof(x_LNCM_3)/sizeof(double) - 1;
	double U;
	const double xmin = x_LNCM_3[nmin];
	const double xmax = x_LNCM_3[nmax];
	if(x>=xmin && x<=xmax)
	{
		while(nmax - nmin>1)
		{
			nmid = (nmin + nmax)/2;
			if(x>x_LNCM_3[nmid] && x<x_LNCM_3[nmax]) nmin = nmid;
			else if(x>x_LNCM_3[nmin] && x<x_LNCM_3[nmid]) nmax = nmid;
			else if(x==x_LNCM_3[nmin]) return y_LNCM_3[nmin];
			else if(x==x_LNCM_3[nmid]) return y_LNCM_3[nmid];
			else if(x==x_LNCM_3[nmax]) return y_LNCM_3[nmax];
			icount ++;
		}
		U = y_LNCM_3[nmin] + (x - x_LNCM_3[nmin])/(x_LNCM_3[nmax] - x_LNCM_3[nmin])
			*(y_LNCM_3[nmax] - y_LNCM_3[nmin]);
		return U;
	}
	else if(x>=0e0 && x<xmin)
	{
		U = ocp_LNCM_3(xmin, T, is);
		U = U + (mdata[ACT][NCM].U0 - U)*(xmin - x)/xmin;
	}
	else if(x>xmax && x<=1e0)
	{
		U = ocp_LNCM_3(xmax, T, is);
		U = U + (mdata[ACT][NCM].U1 - U)*(x - xmax)/(1e0 - xmax);
	}
	else
	{
		std::cout<<"Cathode Stoich out of range!"<<std::endl;
		exit(0);
	}
	return U;
}

double ocp_LNCM_4(double x, double T, int is)
{
	// Z. Li, J. Electrochem. Soc., 158, A516, 2011
	// Discharge from 4.4V
	int icount = 0;
	int nmid;
	int nmin = 0;
	int nmax = sizeof(x_LNCM_4)/sizeof(double) - 1;
	double U;
	const double xmin = x_LNCM_4[nmin];
	const double xmax = x_LNCM_4[nmax];
	if(x>=xmin && x<=xmax)
	{
		while(nmax - nmin>1)
		{
			nmid = (nmin + nmax)/2;
			if(x>x_LNCM_4[nmid] && x<x_LNCM_4[nmax]) nmin = nmid;
			else if(x>x_LNCM_4[nmin] && x<x_LNCM_4[nmid]) nmax = nmid;
			else if(x==x_LNCM_4[nmin]) return y_LNCM_4[nmin];
			else if(x==x_LNCM_4[nmid]) return y_LNCM_4[nmid];
			else if(x==x_LNCM_4[nmax]) return y_LNCM_4[nmax];
			icount ++;
		}
		U = y_LNCM_4[nmin] + (x - x_LNCM_4[nmin])/(x_LNCM_4[nmax] - x_LNCM_4[nmin])
			*(y_LNCM_4[nmax] - y_LNCM_4[nmin]);
		return U;
	}
	else if(x>=0e0 && x<xmin)
	{
		U = ocp_LNCM_4(xmin, T, is);
		U = U + (mdata[ACT][NCM].U0 - U)*(xmin - x)/xmin;
	}
	else if(x>xmax && x<=1e0)
	{
		U = ocp_LNCM_4(xmax, T, is);
		U = U + (mdata[ACT][NCM].U1 - U)*(x - xmax)/(1e0 - xmax);
	}
	else
	{
		std::cout<<"Cathode Stoich out of range!"<<std::endl;
		exit(0);
	}
	return U;
}

double ocp_LNCM_5(double x, double T, int is)
{
	// Z. Li, J. Electrochem. Soc., 158, A516, 2011
	// charge to 4.3V
	int icount = 0;
	int nmid;
	int nmin = 0;
	int nmax = sizeof(x_LNCM_5)/sizeof(double) - 1;
	double U;
	const double xmin = x_LNCM_5[nmin];
	const double xmax = x_LNCM_5[nmax];
	if(x>=xmin && x<=xmax)
	{
		while(nmax - nmin>1)
		{
			nmid = (nmin + nmax)/2;
			if(x>x_LNCM_5[nmid] && x<x_LNCM_5[nmax]) nmin = nmid;
			else if(x>x_LNCM_5[nmin] && x<x_LNCM_5[nmid]) nmax = nmid;
			else if(x==x_LNCM_5[nmin]) return y_LNCM_5[nmin];
			else if(x==x_LNCM_5[nmid]) return y_LNCM_5[nmid];
			else if(x==x_LNCM_5[nmax]) return y_LNCM_5[nmax];
			icount ++;
		}
		U = y_LNCM_5[nmin] + (x - x_LNCM_5[nmin])/(x_LNCM_5[nmax] - x_LNCM_5[nmin])
			*(y_LNCM_5[nmax] - y_LNCM_5[nmin]);
		return U;
	}
	else if(x>=0e0 && x<xmin)
	{
		U = ocp_LNCM_5(xmin, T, is);
		U = U + (mdata[ACT][NCM].U0 - U)*(xmin - x)/xmin;
	}
	else if(x>xmax && x<=1e0)
	{
		U = ocp_LNCM_5(xmax, T, is);
		U = U + (mdata[ACT][NCM].U1 - U)*(x - xmax)/(1e0 - xmax);
	}
	else
	{
		std::cout<<"Anode Stoich out of range!"<<std::endl;
		exit(0);
	}
	return U;
}

double ocp_LNCM_6(double x, double T, int is)
{
	// Z. Li, J. Electrochem. Soc., 158, A516, 2011
	// N. Yabuuchi, J. Electrochem. Soc., 154, A314, 2007
	// Average between charge to 4.3V & discharge from 4.3V, the rest is from Yabuuchi
	int icount = 0;
	int nmid;
	int nmin = 0;
	int nmax = sizeof(x_LNCM_6)/sizeof(double) - 1;
	double U;
	const double xmin = x_LNCM_6[nmin];
	const double xmax = x_LNCM_6[nmax];
	if(x>=xmin && x<=xmax)
	{
		while(nmax - nmin>1)
		{
			nmid = (nmin + nmax)/2;
			if(x>x_LNCM_6[nmid] && x<x_LNCM_6[nmax]) nmin = nmid;
			else if(x>x_LNCM_6[nmin] && x<x_LNCM_6[nmid]) nmax = nmid;
			else if(x==x_LNCM_6[nmin]) return y_LNCM_6[nmin];
			else if(x==x_LNCM_6[nmid]) return y_LNCM_6[nmid];
			else if(x==x_LNCM_6[nmax]) return y_LNCM_6[nmax];
			icount ++;
		}
		U = y_LNCM_6[nmin] + (x - x_LNCM_6[nmin])/(x_LNCM_6[nmax] - x_LNCM_6[nmin])
			*(y_LNCM_6[nmax] - y_LNCM_6[nmin]);
		return U;
	}
	else if(x>=0e0 && x<xmin)
	{
		U = ocp_LNCM_6(xmin, T, is);
		U = U + (mdata[ACT][NCM].U0 - U)*(xmin - x)/xmin;
	}
	else if(x>xmax && x<=1e0)
	{
		U = ocp_LNCM_6(xmax, T, is);
		U = U + (mdata[ACT][NCM].U1 - U)*(x - xmax)/(1e0 - xmax);
	}
	else
	{
		std::cout<<"Anode Stoich out of range!"<<std::endl;
		exit(0);
	}
	return U;
}

double ocp_LNCM_7(double x, double T, int is)
{
	// N. Yabuuchi, J. Electrochem. Soc., 154, A314, 2007 Charge to 4.4V data
	double U;
	double xmin = 0.32e0;
	double xmax = 0.9999e0;
	if(x>=xmin && x<=xmax)
	{
		/*U = 5.83e0 -6.541e0*x + 6.907e0*x*x 
			- 0.3038*exp(100e0*x - 99.47e0) - 2.419e0*x*x*x - 0.1211e0*x*x*x*x;*/
		double x2 = x*x;
		double x3 = x2*x;
		double x4 = x3*x;
		U = -10.72*x4 + 23.88*x3 + -16.77*x2 + 2.595*x + 4.563; //4.563;
	}
	else if(x>=0e0 && x<xmin)
	{
		U = ocp_LNCM_7(xmin, T, is);
		U = U + (mdata[ACT][NCM].U0 - U)*(xmin - x)/xmin;
	}
	else if(x>xmax && x<=1e0)
	{
		U = ocp_LNCM_7(xmax, T, is);
		U = U + (mdata[ACT][NCM].U1 - U)*(x - xmax)/(1e0 - xmax);
	}
	else if(x>1e0)
		U = mdata[ACT][NCM].U1;
	else
	{
		std::cout<<"Cathode Stoich out of range!"<<std::endl;
		exit(0);
	}
	return U;
}

double ocp_LNCM_8(double x, double T, int is)
{
	// S. L. Wu, J. Electrochem. Soc., 159, A438, 2012
	// Above 4.3V use the data from N. Yabuuchi, J. Electrochem. Soc., 154, A314, 2007
	int icount = 0;
	int nmid;
	int nmin = 0;
	int nmax = sizeof(x_LNCM_8)/sizeof(double) - 1;
	double U;
	const double xmin = x_LNCM_8[nmin];
	const double xmax = x_LNCM_8[nmax];
	if(x>=xmin && x<=xmax)
	{
		while(nmax - nmin>1)
		{
			nmid = (nmin + nmax)/2;
			if(x>x_LNCM_8[nmid] && x<x_LNCM_8[nmax]) nmin = nmid;
			else if(x>x_LNCM_8[nmin] && x<x_LNCM_8[nmid]) nmax = nmid;
			else if(x==x_LNCM_8[nmin]) return y_LNCM_8[nmin];
			else if(x==x_LNCM_8[nmid]) return y_LNCM_8[nmid];
			else if(x==x_LNCM_8[nmax]) return y_LNCM_8[nmax];
			icount ++;
		}
		U = y_LNCM_8[nmin] + (x - x_LNCM_8[nmin])/(x_LNCM_8[nmax] - x_LNCM_8[nmin])
			*(y_LNCM_8[nmax] - y_LNCM_8[nmin]);
		return U;
	}
	else if(x>=0e0 && x<xmin)
	{
		U = ocp_LNCM_8(xmin, T, is);
		U = U + (mdata[ACT][NCM].U0 - U)*(xmin - x)/xmin;
	}
	else if(x>xmax && x<=1e0)
	{
		U = ocp_LNCM_8(xmax, T, is);
		U = U + (mdata[ACT][NCM].U1 - U)*(x - xmax)/(1e0 - xmax);
	}
	else
	{
		std::cout<<"Anode Stoich out of range!"<<std::endl;
		exit(0);
	}
	return U;
}

double ocp_LNCM_9(double x, double T, int is)
{
	// S. L. Wu, J. Electrochem. Soc., 159, A438, 2012
	// Above 4.3V use the data from N. Yabuuchi, J. Electrochem. Soc., 154, A314, 2007
	int icount = 0;
	int nmid;
	int nmin = 0;
	int nmax = sizeof(y_LNCM_9)/sizeof(double) - 1;
	double U;
	const double xmin = x_LNCM_9[nmin];
	const double xmax = x_LNCM_9[nmax];
	if(x>=xmin && x<=xmax)
	{
		while(nmax - nmin>1)
		{
			nmid = (nmin + nmax)/2;
			if(x>x_LNCM_9[nmid] && x<x_LNCM_9[nmax]) nmin = nmid;
			else if(x>x_LNCM_9[nmin] && x<x_LNCM_9[nmid]) nmax = nmid;
			else if(x==x_LNCM_9[nmin]) return y_LNCM_9[nmin];
			else if(x==x_LNCM_9[nmid]) return y_LNCM_9[nmid];
			else if(x==x_LNCM_9[nmax]) return y_LNCM_9[nmax];
			icount ++;
		}
		U = y_LNCM_9[nmin] + (x - x_LNCM_9[nmin])/(x_LNCM_9[nmax] - x_LNCM_9[nmin])
			*(y_LNCM_9[nmax] - y_LNCM_9[nmin]);
		return U;
	}
	else if(x>=0e0 && x<xmin)
	{
		U = ocp_LNCM_9(xmin, T, is);
		U = U + (mdata[ACT][NCM].U0 - U)*(xmin - x)/xmin;
	}
	else if(x>xmax && x<=1e0)
	{
		U = ocp_LNCM_9(xmax, T, is);
		U = U + (mdata[ACT][NCM].U1 - U)*(x - xmax)/(1e0 - xmax);
	}
	else
	{
		std::cout<<"Anode Stoich out of range!"<<std::endl;
		exit(0);
	}
	return U;
}
double ocp_LNCM622_1(double x, double T, int is)
{
	int icount = 0;
	int nmid;
	int nmin = 0;
	int nmax = sizeof(y_LNCM622_1)/sizeof(double) - 1;
	double U;
	const double xmin = x_LNCM622_1[nmin];
	const double xmax = x_LNCM622_1[nmax];
	if(x>=xmin && x<=xmax)
	{
		while(nmax - nmin>1)
		{
			nmid = (nmin + nmax)/2;
			if(x>x_LNCM622_1[nmid] && x<x_LNCM622_1[nmax]) nmin = nmid;
			else if(x>x_LNCM622_1[nmin] && x<x_LNCM622_1[nmid]) nmax = nmid;
			else if(x==x_LNCM622_1[nmin]) return y_LNCM622_1[nmin];
			else if(x==x_LNCM622_1[nmid]) return y_LNCM622_1[nmid];
			else if(x==x_LNCM622_1[nmax]) return y_LNCM622_1[nmax];
			icount ++;
		}
		U = y_LNCM622_1[nmin] + (x - x_LNCM622_1[nmin])/(x_LNCM622_1[nmax] - x_LNCM622_1[nmin])
			*(y_LNCM622_1[nmax] - y_LNCM622_1[nmin]);
		return U;
	}
	else if(x>=0e0 && x<xmin)
	{
		U = ocp_LNCM622_1(xmin, T, is);
		U = U + (mdata[ACT][NCM622].U0 - U)*(xmin - x)/xmin;
	}
	else if(x>xmax && x<=1e0)
	{
		U = ocp_LNCM622_1(xmax, T, is);
		U = U + (mdata[ACT][NCM622].U1 - U)*(x - xmax)/(1e0 - xmax);
	}
	else
	{
		std::cout<<"Cathode Stoich out of range!"<<std::endl;
		exit(0);
	}
//	std::cout<<"x="<<x<<"\t"<<"U="<<U<<std::endl;
	return U;
}
double ocp_LNCM622_2(double x, double T, int is)
{
	double xx_ocp[54]=
	{0.0e0, 2.610000E-01, 2.776070E-01, 2.942140E-01, 3.108210E-01, 3.274280E-01, 3.440350E-01, 3.606420E-01, 3.772490E-01, 
	 3.938560E-01, 4.104630E-01, 4.270700E-01, 4.436770E-01, 4.603579E-01, 4.769649E-01, 4.935719E-01, 5.101789E-01, 5.267859E-01, 
	 5.433929E-01, 5.599999E-01, 5.766069E-01, 5.932139E-01, 6.098209E-01, 6.264279E-01, 6.430349E-01, 6.596419E-01, 6.762489E-01, 
	 6.928559E-01, 7.094629E-01, 7.260699E-01, 7.426769E-01, 7.592839E-01, 7.758909E-01, 7.924980E-01, 8.091050E-01, 8.257120E-01, 
	 8.423190E-01, 8.589260E-01, 8.756068E-01, 8.922138E-01, 9.088208E-01, 9.254278E-01, 9.420348E-01, 9.492700E-01, 9.550000E-01, 
	 9.600000E-01, 9.650000E-01, 9.700000E-01, 9.750000E-01, 9.800000E-01, 9.850000E-01, 9.900000E-01, 9.950000E-01, 1.000000E+00};

	double ocp_NCM622[54]=
	{4.800e0, 4.2726E+00, 4.239000E+00, 4.207100E+00, 4.175700E+00, 4.145100E+00, 4.115100E+00, 4.086100E+00, 4.058200E+00, 
	 4.031300E+00, 4.004900E+00, 3.979000E+00, 3.953400E+00, 3.928300E+00, 3.903500E+00, 3.880200E+00, 3.858200E+00, 3.837900E+00, 
	 3.819900E+00, 3.804200E+00, 3.790900E+00, 3.779100E+00, 3.768700E+00, 3.759300E+00, 3.750600E+00, 3.742000E+00, 3.733900E+00, 
	 3.725500E+00, 3.716900E+00, 3.707800E+00, 3.698400E+00, 3.688500E+00, 3.678200E+00, 3.667500E+00, 3.656600E+00, 3.645600E+00, 
	 3.634400E+00, 3.623100E+00, 3.611100E+00, 3.598000E+00, 3.582800E+00, 3.564100E+00, 3.539200E+00, 3.526200E+00, 3.504580E+00,
	 3.483240E+00, 3.456450E+00, 3.423070E+00, 3.381810E+00, 3.331230E+00, 3.269720E+00, 3.195510E+00, 3.106680E+00, 3.001080E+00};

	int N_OCP = 54;

	double ocp1;
	int i;
	int a1, a2;
	a1 = a2 = -1;
	
	for (i=0; (i<N_OCP)&&(a2 <0); i++)
	{
		if(x >=xx_ocp[i] && x <= xx_ocp[i+1])
		{
			a1 = i;
			a2 = i+1;
		}
	}

	double x1,x2;

	x1 = xx_ocp[a1];
	x2 = xx_ocp[a2];

	if(x1==x2)
		ocp1=ocp_NCM622[a1];
	else
		ocp1=ocp_NCM622[a1]+(ocp_NCM622[a2]-ocp_NCM622[a1])*(x-x1)/(x2-x1);

	std::cout<<"x="<<x<<"\t"<<"ocp="<<ocp1<<std::endl;

	return ocp1;
}

double ocp_LFPO_1(double x, double T, int is)
{
	// M. Safari .etc, J. Electrochem. Soc., 158, A63, 2011
	double U;
	double xmin = 0e0;
	double xmax = 1e0;
	if(x>=xmin && x<=xmax)
	{
		U = 3.4323e0 - 0.8428e0*exp(-80.2493e0*pow(1e0-x, 1.3198e0))
			- 3.247e-6*exp(20.2645e0*pow(1e0-x, 3.8003e0))
			+ 3.2482e-6*exp(20.2646e0*pow(1e0-x, 3.7995)) - x*1e-4;
	}
	else if(x>=0e0 && x<xmin)
	{
		U = ocp_LFPO_1(xmin, T, is);
		U = U + (mdata[ACT][LFP].U0 - U)*(xmin - x)/xmin;
	}
	else if(x>xmax && x<=1e0)
	{
		U = ocp_LFPO_1(xmax, T, is);
		U = U + (mdata[ACT][LFP].U1 - U)*(x - xmax)/(1e0 - xmax);
	}
	else
	{
		std::cout<<"Cathode Stoich out of range!"<<std::endl;
		exit(0);
	}
	return U;
}

double ocp_LFPO_2(double x, double T, int is)
{
	// V. Srinivasan .etc, J. Electrochem. Soc., 151, A1517, 2004
	double U;
	double xmin = 0e0;
	double xmax = 1e0;
	if(x>=xmin && x<=xmax)
	{
		U = 3.114559e0 + 4.438792e0*atan(-71.7352e0*x + 70.85337e0)
			- 4.240252e0*atan(-68.5605e0*x + 67.730082e0);
	}
	else if(x>=0e0 && x<xmin)
	{
		U = ocp_LFPO_2(xmin, T, is);
		U = U + (mdata[ACT][LFP].U0 - U)*(xmin - x)/xmin;
	}
	else if(x>xmax && x<=1e0)
	{
		U = ocp_LFPO_2(xmax, T, is);
		U = U + (mdata[ACT][LFP].U1 - U)*(x - xmax)/(1e0 - xmax);
	}
	else
	{
		std::cout<<"Cathode Stoich out of range!"<<std::endl;
		exit(0);
	}
	return U;
}

double ocp_LFPO_3(double stoich, double T, int is)
{
	// Coda experiment
	stoich = 1e0 - stoich;
    double ocpC_;
    double Uf,Umax,Umin,Ecrit;
    double YbaMax,YbaMin;
    double Yab,Yba;
    double Eab,Eba,atanh_ab,atanh_ba;

    Ecrit = 0.99e0;
    Umax = 3.5e0;
    Uf = 3.43e0;
    Umin = 1.5e0;

	// Yab and Yba is function of temp
    YbaMin = 0.08e0;
    YbaMax = 0.8e0;
    Yba = YbaMin+(YbaMax-YbaMin)*(313.15e0-T)/(30e0+40e0);
    if(T>313.15e0) Yba=YbaMin;
    Yab=0.96e0;

    atanh_ba = 0.5e0*log((1e0+Ecrit)/(1e0-Ecrit));
    atanh_ab = -atanh_ba;
    Eab = (Yab-1e0)/atanh_ab;
    Eba = Yba/atanh_ba;

	ocpC_=Umin+(Uf-Umin)*tanh(stoich/Eba)+(Umax-Uf)*(1e0+tanh((stoich-1e0)/Eab));

    return ocpC_;
}

double cnd_elc_LI(double x, double T, int is)
{
	// from wiki
	const double R20 = 9.28e-8;	// ohm m
	const double alpha = 3.9e-3;		// K-1
	if(!is) T = Tcell0;
	double cnd = 1e0/(R20 + alpha*(T-293.15));
	return cnd;
}

double cnd_elc_CU(double x, double T, int is)
{
	// From Wiki
	const double R20 = 1.68e-8;	// ohm m
	const double alpha = 3.9e-3;		// K-1
	if(!is) T = Tcell0;
	double cnd = 1e0/(R20 + alpha*(T-293.15));
	return cnd;
}

double cnd_elc_AL(double x, double T, int is)
{
	// From Wiki
	const double R20 = 2.82e-8;	// ohm m
	const double alpha = 3.9e-3;		// K-1
	if(!is) T = Tcell0;
	double cnd = 1e0/(R20 + alpha*(T-293.15));
	return cnd;
}

double cnd_elc_MCMB(double x, double T, int is)
{
	//const double Eact = 1e4;			// Activation energy for conductivity
	double cnd = 1e2;
	//if(is)cnd *= exp(Eact/ugc*(1e0/T0-1e0/T));
	return cnd;
}

double cnd_elc_LTO(double x, double T, int is)
{
	// S. Stewart .etc, J Electrochem Soc, 155, A253, 2008
	return 2e-2;
}

double cnd_elc_LCO(double x, double T, int is)
{
	// M. Doyle, Y. Fuentes, J. Electrochem. Soc., 150, A706, 2003
	return 1e1;
}

double cnd_elc_LMO_1(double x, double T, int is)
{
	// M. Doyle, J. Newman, J. Electrochem. Soc., 143, 1890, 1996
	// P. Arora, .etc, J. Power Sources, 88, 219, 2000
	return 3.8e0;
}

double cnd_elc_LNCM(double x, double T, int is)
{
	// unknown
	//const double Eact = 1e4;			// Activation energy for conductivity
	//const double Tref = 298.15e0;
	double cnd = 1e1;
	//if(is)cnd *= exp(Eact/ugc*(1e0/Tref-1e0/T));
	return cnd;
}
double cnd_elc_LNCM622(double x, double T, int is)
{
	// Assumed the same as NCM111; unknown
	//const double Eact = 1e4;			// Activation energy for conductivity
	//const double Tref = 298.15e0;
	double cnd = 1e1;
	//if(is)cnd *= exp(Eact/ugc*(1e0/Tref-1e0/T));
	return cnd;
}

double cnd_elc_LFPO_1(double x, double T, int is)
{
	// V. Srinivasan .etc, J. Electrochem. Soc., 151, A1517, 2004
	return 5e-3;
}

double cnd_elc_LFPO_2(double x, double T, int is)
{
	// our original code;
	const double Eact = 3e4;			// Activation energy for conductivity
	double cnd = 3e-2;
	if(is)cnd *= exp(Eact/ugc*(1e0/T0-1e0/T));
	return cnd;
}

double cnd_ion_sln1(double x, double T, int is)
{
	const double Eact = 5.5e4;			// Activation energy for ionic conductivity of electrolyte solution*/
	double dphie_;
	double ccm3 = x*1e-6;
	
	// Modified equation from Gu's paper (LiyMn2O4) to match Doyle's 2003 paper (LiyCoO2)
	// dphie_=0.0158*(ccm3*1e3)*exp(-0.85*pow((ccm3*1e3),1.4));
	double x2 = ccm3*ccm3;
	double x3 = x2*ccm3;
	double x4 = x3*ccm3;
 
    dphie_ = (4.1253e-4 + 5.007*ccm3 - 4.7212e3*x2 + 1.5094e6*x3 - 1.6018e8*x4)*1e2;

	if(is)dphie_=dphie_*exp(Eact/ugc*(1/T0-1/T));

    return dphie_;
}

double cnd_ion_sln2(double x, double T, int is)
{
	// LiPF6 in PC(10%)-EC(27%)-DMC(63%)
	// L Valoen & J Reimers, J. Electrochem. Soc., 152, A882, 2005
	double cnd_ion;
	double xmin = 0e0;
	double xmax = 5e3;
	double Tmin = 263.15e0;
	double Tmid = 273.15e0;
	double dT = Tmid - Tmin;
	//const double Tref = 298.15e0;
	//const double Eact = 4.5e4;
	if(!is) T = T0;
	if(T>=Tmin || x<=0.1e3)
	{
		if(x>=xmin && x<=xmax)
		{
			x *= 1e-3;		// from mol/m3 to mol/L
			cnd_ion = -10.5e0 + 0.0740e0*T - 6.96e-5*T*T
				+ (0.668e0 -0.0178*T + 2.80e-5*T*T)*x + (0.494e0 -8.86e-4*T)*x*x;
			//cnd_ion = -10.5e0 + 0.0740e0*Tref - 6.96e-5*Tref*Tref
			//	+ (0.668e0 -0.0178*Tref + 2.80e-5*Tref*Tref)*x + (0.494e0 -8.86e-4*Tref)*x*x;
			cnd_ion *= cnd_ion;
			cnd_ion *= x;
			//cnd_ion *= exp(Eact/ugc*(1e0/298.15-1e0/T));
			cnd_ion *= 0.1e0;		// from mS/cm to S/m
		}
		else if(x>=0e0 && x<xmin)
			cnd_ion = cnd_ion_sln2(xmin, T, is);
		else if(x>xmax)
			cnd_ion = cnd_ion_sln2(xmax, T, is);
		else
		{
			std::cout<<"Electrolyte concentration less than 0!"<<std::endl;
			exit(0);
		}
	}
	else
	{
		double yh = log(cnd_ion_sln2(x, Tmid + dT, 1));
		double ym = log(cnd_ion_sln2(x, Tmid, 1));
		double yl = log(cnd_ion_sln2(x, Tmin, 1));
		double a = ((yh + yl)/2 - ym)/(dT*dT);
		double b = ((yh - yl)/2 - 2*a*Tmid*dT)/dT;
		double c = ym - a*(Tmid*Tmid) - b*Tmid;
		cnd_ion = a*T*T + b*T + c;
		cnd_ion = exp(cnd_ion);
	}
	return cnd_ion;
}
double cnd_ion_sln2_R2(double x, double T, int is)
{
	// LiPF6 in PC(10%)-EC(27%)-DMC(63%)
	// L Valoen & J Reimers, J. Electrochem. Soc., 152, A882, 2005
	double cnd_ion;
	double xmin = 0e0;
	double xmax = 4e3;
	double Tmin = 233.15e0;
	double Tmid = 273.15e0;
	double dT = Tmid - Tmin;
	const double Tref = 298.15e0;
	const double Eact = 20e3;
	if(!is) T = T0;
	if(T>=Tmin || x<=0.1e3)
	{
		if(x>=xmin && x<=xmax)
		{
			x *= 1e-3;		// from mol/m3 to mol/L
			//cnd_ion = -10.5e0 + 0.0740e0*T - 6.96e-5*T*T
			//	+ (0.668e0 -0.0178*T + 2.80e-5*T*T)*x + (0.494e0 -8.86e-4*T)*x*x;
			cnd_ion = -10.5e0 + 0.0740e0*Tref - 6.96e-5*Tref*Tref
				+ (0.668e0 -0.0178*Tref + 2.80e-5*Tref*Tref)*x + (0.494e0 -8.86e-4*Tref)*x*x;
			cnd_ion *= cnd_ion;
			cnd_ion *= x;
			cnd_ion *= exp(Eact/ugc*(1e0/298.15-1e0/T));
			cnd_ion *= 0.1e0;		// from mS/cm to S/m
		}
		else if(x>=0e0 && x<xmin)
			cnd_ion = cnd_ion_sln2(xmin, T, is);
		else if(x>xmax)
			cnd_ion = cnd_ion_sln2(xmax, T, is);
		else
		{
			std::cout<<"Electrolyte concentration less than 0!"<<std::endl;
			exit(0);
		}
	}
	else
	{
		double yh = log(cnd_ion_sln2(x, Tmid + dT, 1));
		double ym = log(cnd_ion_sln2(x, Tmid, 1));
		double yl = log(cnd_ion_sln2(x, Tmin, 1));
		double a = ((yh + yl)/2 - ym)/(dT*dT);
		double b = ((yh - yl)/2 - 2*a*Tmid*dT)/dT;
		double c = ym - a*(Tmid*Tmid) - b*Tmid;
		cnd_ion = a*T*T + b*T + c;
		cnd_ion = exp(cnd_ion);
	}
	return cnd_ion;
}

double cnd_ion_FGR(double x, double T, int is)
{
	const double cnd_ref = 5e-6*4.0;		// [S/m]
	const double Tref = 298.15e0;
	const double Eact = 35e3;//+25e3;
	if(!is) T = T0;
	double cnd = cnd_ref*exp(Eact/ugc*(1/Tref-1/T));
	return cnd;
}

double cnd_ion_FLMO(double x, double T, int is)
{
	const double cnd_ref = 5e-6*3;		// [S/m]
	const double Tref = 298.15e0;
	const double Eact = 65e3*0.5;
	if(!is) T = T0;
	double cnd = cnd_ref*exp(Eact/ugc*(1/Tref-1/T));
	return cnd;
}

double cnd_ion_FNCM(double x, double T, int is)
{
	const double cnd_ref = 5e-6;		// [S/m]
	const double Tref = 298.15e0;
	const double Eact = 35e3;//+20e3;
	if(!is) T = T0;
	double cnd = cnd_ref*exp(Eact/ugc*(1/Tref-1/T));
	return cnd;
}

double dif_Li_LI(double x, double T, int is)
{
	return 1e-12;
}

double dif_Li_MCMB_1(double xsoc, double T, int is)
{
	double dCsA;
    double d_ref,xp;
 
    d_ref=0.5e-11+0.7e-11*(T-263.15)/10.0;
    xp=0;
    if(T<263.15){d_ref=0.5e-11-(263.15-T)*0.1e-11/10.0;xp=0e0;}
    else if(T<273.15)xp=1.2+1.6*(T-263.15)/10.0;
    else if(T<298.15)xp=2.8+0.7*(T-273.15)/25.0;
    else if(T>=298.15)xp=3.5+0.2*(T-298.15)/25.0;

	dCsA=d_ref*pow(1.5-xsoc,xp)/pow(0.5,xp);
 
    if(dCsA<5e-12)  dCsA=5e-12;            /* Minimum value */

	dCsA =  dCsA*1e-4;

    return dCsA;
}

double dif_Li_MCMB_2(double x, double T, int is)
{
	double dif;
	double xmin = 0e0;
	double xmax = 1e0;
	double Eact = 35e3-5e3; 
	double Tref = 298.15e0;
	if(!is) T = T0;
	if(x>=xmin && x<=xmax)
	{
		dif = 1.6e-14*exp(Eact/ugc*(1e0/Tref - 1e0/T))*1.5;
		dif *= pow(1.5e0 - x,1.5);//XG from ACB
		//dif *= pow(x+0.5, 1.3);
	}
	else if(x>=0e0 && x<xmin)
		dif = dif_Li_MCMB_2(xmin, T, is);
	else if(x>xmax)
		dif = dif_Li_MCMB_2(xmax, T, is);
	else
	{
		std::cout<<"Anode stoich less than 0!"<<std::endl;
		exit(0);
	}
	return dif;
}

double dif_Li_MCMB_3(double x, double T, int is)
{
	// M. Doyle, Y. Fuentes, J. Electrochem. Soc., 150, A706, 2003
	return 5.5e-14;
}

double dif_Li_MCMB_4(double x, double T, int is)
{
	// K. Kumaresan .etc, J. Electrochem. Soc., 155, A164, 2008
	double dif;
	dif = 3e-13; //1.4523e-13;
	if(is) dif *= exp(68025.7e0/ugc*(1e0/318e0 - 1/T));
	return dif;
}

double dif_Li_MCMB_5(double x, double T, int is)
{
	// M. Nishizawa .etc, Electrochem. & Solid-State Letters, 1, 10, 1998
	int icount = 0;
	int nmid;
	int nmin = 0;
	int nmax = sizeof(x_dif_Li_MCMB_5)/sizeof(double) - 1;
	double dif;
	double Eact = 30e3 + 0e3; //62//3.5e4;
	double Tref = 298.15e0;
	const double xmin = x_dif_Li_MCMB_5[nmin];
	const double xmax = x_dif_Li_MCMB_5[nmax];
	if(x>=xmin && x<=xmax)
	{
		while(nmax - nmin>1)
		{
			nmid = (nmin + nmax)/2;
			if(x>x_dif_Li_MCMB_5[nmid] && x<x_dif_Li_MCMB_5[nmax]) nmin = nmid;
			else if(x>x_dif_Li_MCMB_5[nmin] && x<x_dif_Li_MCMB_5[nmid]) nmax = nmid;
			else if(x==x_dif_Li_MCMB_5[nmin]) return exp(y_dif_Li_MCMB_5[nmin]+Eact/ugc*(1e0/Tref - 1e0/T))*2e-1;
			else if(x==x_dif_Li_MCMB_5[nmid]) return exp(y_dif_Li_MCMB_5[nmid]+Eact/ugc*(1e0/Tref - 1e0/T))*2e-1;
			else if(x==x_dif_Li_MCMB_5[nmax]) return exp(y_dif_Li_MCMB_5[nmax]+Eact/ugc*(1e0/Tref - 1e0/T))*2e-1;
			icount ++;
		}
		dif = y_dif_Li_MCMB_5[nmin] + (x - x_dif_Li_MCMB_5[nmin])/(x_dif_Li_MCMB_5[nmax] - x_dif_Li_MCMB_5[nmin])
			*(y_dif_Li_MCMB_5[nmax] - y_dif_Li_MCMB_5[nmin]);
		//std::cout<<x<<" "<<icount<<std::endl;
		return exp(dif+Eact/ugc*(1e0/Tref - 1e0/T))*2e-1;
	}
	else if(x>=0e0 && x<xmin)
	{
		dif = dif_Li_MCMB_5(xmin, T, is);
	}
	else if(x>xmax && x<=1e0)
	{
		dif = dif_Li_MCMB_5(xmax, T, is);
	}
	else
	{
		std::cout<<"Anode dif stoich out of range!"<<std::endl;
		exit(0);
	}
	return dif;
}

double dif_Li_LTO(double x, double T, int is)
{
	// Y. H. Rho and K. Kanamura, J Solid State Chem, 177, 2094 (2004).
	// J. Christensen .etc, J Electrochem Soc, 153, A560 (2006).
	return 6.8e-15;
}

double dif_Li_LTO_1(double x, double T, int is)
{
	// Y. Rho .etc, J. Solid State Chem., 177, 2094, 2004
	// J. Christensen .etc, J. Electrochem. Soc., 153, A560, 2006
	return 6.8e-15;
}

double dif_Li_LTO_2(double x, double T, int is)
{
	// M. Wagemaker, J. Phys. Chem. B, 113, 224, 2009
	return 4.0e-16;
}

double dif_Li_LCO(double cs, double T, int is)
{
	return 1e-11;	// M. Doyle, J. Electrochem. Soc., 150, A706, 2003
	//return 5e-13;	// M. Whittingham, Chem. Rev., 104, 4271, 2004
}

double dif_Li_LMO_1(double cs, double T, int is)
{
	// diffusivity in composite electrodes
	return 1e-13;				// Average value
	// T. Fuller .etc, J. Electrochem. Soc., 141, 1, 1994
	// M. Doyle, J. Newman, J. Electrochem. Soc., 143, 1890, 1996
	// P. Arora, .etc, J. Power Sources, 88, 219, 2000

	// 0.5~1.5e-13;		// D. Guyomard .etc, J. Electrochem. Soc., 139, 937, 1992
	// 0.66~1.4e-14;		// H. Kanoh .etc, J. Electrochem. Soc., 142, 702, 1995
	// 4.89e-13;			// Y. Xia .etc, J. Power Sources, 56, 61, 1995
	// 5e-14;			// D. Totir .etc, Electrochim. Acta, 45, 161, 1999
	// 2.2e-13;			// D. Zhang .etc, J. Electrochem. Soc., 147, 831, 2000
}

double dif_Li_LMO_2(double cs, double T, int is)
{
	// diffusivity in thin film
	return 1e-15;				// Average value

	// 3.5e-15;			// K. Striebel .etc, J. Electrochem. Soc., 143, 1821, 1996
	// 6.1e-16;			// M. Nishizawa .etc, Bull. Chem. Soc. Jpn., 71, 2011, 1998
	// 0.3~5.5e-15;		// D. Shu .etc, J. Power Sources, 114, 253, 2003
	// 0.47~5.96e-16;	// S. Das .etc, J. Power Sources, 139, 261, 2005
	// 0.46~1.04e-15;	// S. Tang .etc, Mater. Chem. Phys., 111, 149, 2008
}

double dif_Li_LMO_3(double cs, double T, int is)
{
	// diffusivity in single partical
	return 1e-15;				// Average value

	// 0.32~1.2e-15;		// M. Chung .etc, J. Electrochem. Soc., 158, A371, 2011
}

double dif_Li_LMO_4(double x, double T, int is)
{
	const double Eact = 30e3;
	const double Tref = 298.15e0;
	const double Dref = 5e-14;
	if(!is)T = T0;
	double dif = Dref*exp(Eact/ugc*(1e0/Tref - 1e0/T));
	return dif;
}

double dif_Li_LMO_5(double x, double T, int is)
{
	const double Eact = 20e3 + 10e3;
	const double Tref = 298.15e0;
	// Dokko JES 2003 PITT
	int icount = 0;
	int nmid;
	int nmin = 0;
	int nmax = sizeof(x_dif_Li_LMO_5)/sizeof(double) - 1;
	double dif;
	const double xmin = x_dif_Li_LMO_5[nmin];
	const double xmax = x_dif_Li_LMO_5[nmax];
	if(x>=xmin && x<=xmax)
	{
		while(nmax - nmin>1)
		{
			nmid = (nmin + nmax)/2;
			if(x>x_dif_Li_LMO_5[nmid] && x<x_dif_Li_LMO_5[nmax]) nmin = nmid;
			else if(x>x_dif_Li_LMO_5[nmin] && x<x_dif_Li_LMO_5[nmid]) nmax = nmid;
			else if(x==x_dif_Li_LMO_5[nmin]) return y_dif_Li_LMO_5[nmin];
			else if(x==x_dif_Li_LMO_5[nmid]) return y_dif_Li_LMO_5[nmid];
			else if(x==x_dif_Li_LMO_5[nmax]) return y_dif_Li_LMO_5[nmax];
			icount ++;
		}
		dif = y_dif_Li_LMO_5[nmin] + (x - x_dif_Li_LMO_5[nmin])/(x_dif_Li_LMO_5[nmax] - x_dif_Li_LMO_5[nmin])
			*(y_dif_Li_LMO_5[nmax] - y_dif_Li_LMO_5[nmin]);
		//return pow(10, dif);
		dif = pow(10, dif);;
	}
	else if(x>=0e0 && x<xmin)
	{
		dif = pow(10, y_dif_Li_LMO_5[nmin]);
	}
	else if(x>xmax && x<=1e0)
	{
		dif = pow(10, y_dif_Li_LMO_5[nmax]);
	}
	else
	{
		std::cout<<"LMO Stoich out of range!"<<std::endl;
		exit(0);
	}
	//return pow(10, dif)*exp(Eact/ugc*(1e0/Tref - 1e0/T));
	dif *= exp(Eact/ugc*(1e0/Tref - 1e0/T));
	return dif;
}

double dif_Li_LNCM_1(double cs, double T, int is)
{
	//  K. Shaju .etc, J Electrochem Soc, 151, A1324, 2004
	return 1e-14;
}

double dif_Li_LNCM_2(double x, double T, int is)
{
	// ECEC Kwon GITT
	const double Eact = 50e3;// + 10e3;// +10e3; //50//32174e0;
	const double Tref = 298.15e0;
	const double Dref = 1.5e-14;//*1.5/1.5; //1.5324e-14;
	if(!is)T = T0;
	double dif = Dref*exp(Eact/ugc*(1e0/Tref - 1e0/T));
	//dif *= pow(1.5e0 - x,2);
	dif *= 1e0 + tanh(-7.0e0*(x - 0.6e0)) + 0.02e0;
	//dif *= 1e0 + tanh(-20e0*(x - 0.73e0)) + 0.02e0;
	return dif;
}

double dif_Li_LNCM_3(double x, double T, int is)
{
	// S. L. Wu, J Electrochem Soc, 159, A438, 2012
	const double Eact = 30e3 + 10e3;
	const double Tref = 298.15e0;
	if(!is) T = T0;
	//if(x >= 0.4e0) x = 0.4 + (x - 0.4)*0.6/0.54;
	double x2 = x*x;
	double x3 = x*x2;
	double dif;
	if(x > 0.71e0) dif = 1.8*pow(10, (90.0353*x2 + -119.2131*x + 27.7260)/(x3 - 8.5573*x2 + 9.8790*x - 2.2320))*exp(Eact/ugc*(1e0/Tref - 1e0/T));
	else dif = 2.5e-14*exp(Eact/ugc*(1e0/Tref - 1e0/T));//dif_Li_LNCM_3(0.867e0, T, is);
	return dif;
}

double dif_Li_LNCM622_1(double x, double T, int is)
{
	//Multi-linear fit of data measured by Yongjun From ECEC
	//be careful of the cut-off diffusivity

	double T1, T2, Tc;
	double Ds_T1, Ds_T2;
	double dif_cut = 1.0e-14;//5.0e-12;
	double diff;

	Tc=T-273.15;

	if(Tc <= -30.0)	//When Tc<-30 oc, assume constant dif the same as T=-30 oC
	{
		T1=-30.0;
		T2=-30.0;
		Ds_T1 = NCM622_Ds_TM30_MLinear_1(x,dif_cut);
		Ds_T2 = NCM622_Ds_TM30_MLinear_1(x,dif_cut);
	}
	else if(Tc <=-15.0)
	{
		T1 = -15.0;
		T2 = -30.0;
		Ds_T1 = NCM622_Ds_TM15_MLinear_1(x,dif_cut);
		Ds_T2 = NCM622_Ds_TM30_MLinear_1(x,dif_cut);
	}
	else if(Tc <=0.0)
	{
		T1 = 0.0;
		T2 = -15.0;
		Ds_T1 = NCM622_Ds_T00_MLinear_1(x,dif_cut);
		Ds_T2 = NCM622_Ds_TM15_MLinear_1(x,dif_cut);
	}
	else if(Tc <=20.0)
	{
		T1 = 20.0;
		T2 = 0.0;
		Ds_T1 = NCM622_Ds_T20_MLinear_1(x,dif_cut);
		Ds_T2 = NCM622_Ds_T00_MLinear_1(x,dif_cut);
	}
	else if(Tc <=40.0)
	{
		T1 = 40.0;
		T2 = 20.0;
		Ds_T1 = NCM622_Ds_T40_MLinear_1(x,dif_cut);
		Ds_T2 = NCM622_Ds_T20_MLinear_1(x,dif_cut);
	}
	else
	{
		T1 = 60.0;
		T2 = 40.0;
		Ds_T1 = NCM622_Ds_T60_MLinear_1(x,dif_cut);
		Ds_T2 = NCM622_Ds_T40_MLinear_1(x,dif_cut);
	}

	diff = NCM622_interpolation(Tc,T1,T2,Ds_T1,Ds_T2);

	diff *=1.0e-4;
	
	diff*=6.0;
	return diff;
}
double dif_Li_LNCM622_2(double x, double T, int is)
{
	int N_ds = 47; // Number of data points measured

	/*Lithium Stoichiometry*/
	double xx_ds[47]=
	{0.0e0, 2.610000E-01, 2.776070E-01, 2.942140E-01, 3.108210E-01, 3.274280E-01, 3.440350E-01, 3.606420E-01, 3.772490E-01, 
	 3.938560E-01, 4.104630E-01, 4.270700E-01, 4.436770E-01, 4.603579E-01, 4.769649E-01, 4.935719E-01, 5.101789E-01, 5.267859E-01, 
	 5.433929E-01, 5.599999E-01, 5.766069E-01, 5.932139E-01, 6.098209E-01, 6.264279E-01, 6.430349E-01, 6.596419E-01, 6.762489E-01, 
	 6.928559E-01, 7.094629E-01, 7.260699E-01, 7.426769E-01, 7.592839E-01, 7.758909E-01, 7.924980E-01, 8.091050E-01, 8.257120E-01, 
	 8.423190E-01, 8.589260E-01, 8.756068E-01, 8.922138E-01, 9.088208E-01, 9.254278E-01, 9.420348E-01, 9.586418E-01, 9.752488E-01,
	 9.918558E-01, 1.000000E+00};
	/*Solid-phase diffusion coefficient at 60 oC*/
	double Ds60[47]=
	{5.173108E-11+1e-20, 5.173108E-11, 5.097275E-11, 5.112684E-11, 5.034442E-11,4.948997E-11, 4.915717E-11,	4.937893E-11, 4.852051E-11,
	 4.803616E-11, 4.797278E-11, 4.784346E-11, 4.760859E-11, 4.686140E-11, 4.617077E-11, 4.523527E-11, 4.621793E-11, 4.491644E-11,
	 4.088570E-11, 4.371391E-11, 4.194927E-11, 3.956652E-11, 3.768346E-11, 3.893623E-11, 3.735486E-11, 3.717107E-11, 3.525700E-11,
	 3.623496E-11, 3.729205E-11, 3.698214E-11, 3.697696E-11, 3.657491E-11, 3.503509E-11, 3.401561E-11, 3.482308E-11, 3.122722E-11,
	 2.762211E-11, 2.387917E-11, 1.687426E-11, 9.112329E-12, 7.987935E-13, 1.361610E-13, 1.485930E-14, 1.816400E-15, 2.220370E-16,
	 2.714170E-17, 9.682780E-18};
	/*Solid-phase diffusion coefficient at 40 oC*/
	double Ds40[47]=
	{5.335606E-11+1e-20, 5.335606E-11, 5.346646E-11, 5.275549E-11, 5.134627E-11, 5.123236E-11, 5.037658E-11, 5.114239E-11, 4.918975E-11,
	 4.803616E-11, 4.787612E-11, 4.677344E-11, 4.625806E-11, 4.715832E-11, 4.483943E-11, 4.566753E-11, 4.563294E-11, 4.525942E-11, 
	 4.379357E-11, 3.977584E-11, 4.148494E-11, 3.984765E-11, 3.780035E-11, 3.735486E-11, 3.718651E-11, 3.560014E-11, 3.547702E-11,
	 3.394040E-11, 3.482308E-11, 3.362030E-11, 3.287637E-11, 3.301815E-11, 3.411097E-11, 3.080609E-11, 2.936973E-11, 2.469448E-11,
	 1.933053E-11, 1.439117E-11, 9.238536E-12, 4.681541E-12, 1.377167E-12, 1.428198E-13, 1.905096E-14, 2.148620E-15, 2.527110E-16, 
	 2.972280E-17, 1.040500E-17};
	/*Solid-phase diffusion coefficient at 20 oC*/
	double Ds20[47]=
	{4.863143E-11+1e-20, 4.863143E-11, 4.773878E-11, 4.738125E-11, 4.811047E-11, 4.678217E-11, 4.713732E-11, 4.675948E-11, 4.489443E-11,
	 4.655787E-11, 4.437226E-11, 4.583923E-11, 4.504691E-11, 4.389578E-11, 4.365575E-11, 4.456238E-11, 4.276561E-11, 4.320682E-11,
	 4.014049E-11, 4.007014E-11, 3.553738E-11, 3.460712E-11, 3.153584E-11, 3.095700E-11, 3.031286E-11, 2.936973E-11, 2.906139E-11,
	 2.494869E-11, 2.681710E-11, 2.694856E-11, 2.803302E-11, 2.592887E-11, 2.606930E-11, 2.186306E-11, 1.884511E-11, 1.413759E-11, 
	 8.515485E-12, 4.071743E-12, 1.066926E-12, 9.838020E-14, 9.444166E-15, 8.826050E-16, 8.303880E-17, 7.812600E-18, 7.350390E-19, 
	 6.915530E-20, 2.169850E-20};
	/*Solid-phase diffusion coefficient at 0 oC*/
	double Ds00[47]=
	{3.971974E-11+1e-20, 3.971974E-11, 3.767920E-11, 3.651402E-11, 3.717534E-11, 3.574064E-11, 3.609839E-11, 3.699592E-11, 3.487963E-11,
	 3.456174E-11, 3.547954E-11, 3.485332E-11, 3.467064E-11, 3.451188E-11, 3.511632E-11, 3.371526E-11, 3.285456E-11, 3.178562E-11,
	 2.901482E-11, 2.708894E-11, 2.373387E-11, 2.202072E-11, 1.868288E-11, 1.891654E-11, 1.731133E-11, 1.570307E-11, 1.475781E-11,
	 1.456198E-11, 1.331126E-11, 1.284416E-11, 1.119062E-11, 9.070269E-12, 6.163510E-12, 3.565883E-12, 1.525511E-12, 3.220648E-13,
	 2.680642E-14, 2.448620E-15, 2.102390E-16, 1.833170E-17, 1.598430E-18, 1.393740E-19, 1.215270E-20, 1.059650E-21, 9.239560E-23, 
	 8.056400E-24, 2.435290E-24};
	/*Solid-phase diffusion coefficient at -15 oC*/
	double DsM15[47]=
	{3.363357E-11+1e-20,3.363357E-11, 2.959512E-11, 2.908070E-11, 2.824301E-11, 2.807595E-11, 2.798013E-11, 2.676044E-11, 2.609343E-11,
	 2.649912E-11, 2.571601E-11, 2.639006E-11, 2.524789E-11, 2.450149E-11, 2.502048E-11, 2.371381E-11, 2.237797E-11, 2.036942E-11,
	 1.863494E-11, 1.543747E-11, 1.249564E-11, 1.038346E-11, 8.762392E-12, 7.188669E-12, 6.396075E-12, 5.613663E-12, 4.509017E-12, 
	 3.995513E-12, 3.027045E-12, 2.023758E-12, 1.243543E-12, 5.062271E-13, 1.436617E-13, 2.004042E-14, 1.497108E-15, 1.678830E-16, 
	 1.713800E-17, 1.749510E-18, 1.785970E-19, 1.823180E-20, 1.861170E-21, 1.899940E-22, 1.939530E-23, 1.979940E-24, 2.021200E-25,
	 2.063310E-26, 6.738290E-27};
	/*Solid-phase diffusion coefficient at -30 oC*/
	double DsM30[47]=
	{1.088179E-11+1e-20,1.304614E-11, 1.088179E-11, 1.074245E-11, 1.110861E-11, 1.127171E-11, 1.142326E-11, 1.123519E-11, 1.124876E-11, 
	 1.133203E-11, 1.170234E-11, 1.078326E-11, 1.091263E-11, 1.031043E-11, 9.850588E-12, 8.546034E-12, 7.867224E-12, 6.349218E-12, 
	 5.317796E-12, 4.086022E-12, 2.986093E-12, 2.204375E-12, 1.603875E-12, 1.159115E-12, 7.234797E-13, 4.922723E-13, 2.928921E-13,
	 1.407811E-13, 5.292239E-14, 1.394965E-14, 4.658720E-15, 1.466480E-15, 4.616210E-16, 1.453100E-16, 4.574090E-17, 1.432460E-17, 
	 4.509130E-18, 1.419390E-18, 4.467990E-19, 1.406440E-19, 4.427220E-20, 1.393610E-20, 4.386830E-21, 1.380890E-21, 4.346800E-22, 
	 1.368290E-22, 7.762470E-23};

	double T1, T2, Tc;
	double *pD1, *pD2;
	double diff;
	double dif_cut = 3.0e-11;

	Tc=T-273.15;
	
	if(Tc <=-15.0)
	{
		T1 = -15.0;
		T2 = -30.0;
		pD1 = DsM15;
		pD2 = DsM30;
	}
	else if(Tc <=0.0)
	{
		T1 = 0.0;
		T2 = -15.0;
		pD1 = Ds00;
		pD2 = DsM15;
	}
	else if(Tc <=20.0)
	{
		T1 = 20.0;
		T2 = 0.0;
		pD1 = Ds20;
		pD2 = Ds00;
	}
	else if(Tc <=40.0)
	{
		T1 = 40.0;
		T2 = 20.0;
		pD1 = Ds40;
		pD2 = Ds20;
	}
	else
	{
		T1 = 60.0;
		T2 = 40.0;
		pD1 = Ds60;
		pD2 = Ds40;
	}

	double Ds_T1,Ds_T2;

	int i;
	int a1, a2;
	a1 = a2 = -1;

	for (i=0; (i<N_ds)&&(a2 <0); i++)
	{
		if(x >=xx_ds[i] && x <= xx_ds[i+1])
		{
			a1 = i;
			a2 = i+1;
		}
	}

	Ds_T1 = NCM622_interpolation(x, xx_ds[a1],xx_ds[a2],pD1[a1],pD1[a2]);
	Ds_T2 = NCM622_interpolation(x, xx_ds[a1],xx_ds[a2],pD2[a1],pD2[a2]);

	diff = NCM622_interpolation(Tc,T1,T2,Ds_T1,Ds_T2);

	if (diff <=dif_cut)
		diff = dif_cut;

	diff *=1.0e-4;
	return diff;
}

double dif_Li_LFPO_1(double cs, double T, int is)
{
	// V. Srinivasan .etc, J. Electrochem. Soc., 151, A1517, 2004
	return 8e-18;
}

double dif_Li_LFPO_2(double cs, double T, int is)
{
	double dif;
	const double csEquC = 0.03e6;			// Equalibrium concentration of Li [mol/m3]
	const double Eact = 3.5e4;				// Activation energy for diffusion coefficient of Li

	dif = 1e-15;
	if(cs<=csEquC)dif *= 2e0;
	if(is)dif *= exp(Eact/ugc*(1e0/T0-1e0/T));

    return dif;
}

double dif_Li_sln1(double ccm3, double T, int is)
{
	double dif = 2.5e-10; //1.5e-10;				// Diffusion coefficient of Li in electrolyte [m2/s]
	const double Eact = 2.5e4;          // Activation energy for D0 of Li+ in electrolyte solution

	if(is)dif *= exp(Eact/ugc*(1e0/T0-1e0/T));
    return dif;
}

double dif_Li_sln2(double x, double T, int is)
{
	// LiPF6 in PC(10%)-EC(27%)-DMC(63%)
	// L Valoen & J Reimers, J. Electrochem. Soc., 152, A882, 2005
	double dif;
	//const double Eact = 2e4;
	const double xmin = 0e0;
	const double xmax = 4e3;
	const double Tmin = 253.15e0-10e0-10e0;
	const double Tmax = 353.15e0;
	//const double Tref = 298.15e0;
	const double Tg0 = 229e0;
	const double Tg1 = 5e0;
	if(!is) T = T0;
	if(T>=Tmin && T<=Tmax)
	{
		if(x>=xmin && x<=xmax)
		{
			x *= 1e-3;		// from mol/m3 to mol/L
			//dif = -4.43e0 - 54e0/(T - Tg0 - x*Tg1) + (-0.22e0)*x;
			dif = -4.43e0 - 54e0/(298.15 + 0.8*(T-298.15) - Tg0 - x*Tg1) + (-0.22e0)*x;
			dif = exp(dif*log(10e0));
			//dif *= exp(Eact/ugc*(1e0/298.15-1e0/T));
			dif *= 1e-4;		// from cm2/s to m2/s
		}
		else if(x>=0e0 && x<xmin)
			dif = dif_Li_sln2(xmin, T, is);
		else if(x>xmax)
			dif = dif_Li_sln2(xmax, T, is);
		else
		{
			std::cout<<"Electrolyte concentration less than 0!"<<std::endl;
			exit(0);
		}
	}
	else if(T>=0e0 && T<Tmin)
		dif = dif_Li_sln2(x, Tmin, 1);
	else if(T>Tmax)
		dif = dif_Li_sln2(x, Tmax, 1);
	else
	{
		std::cout<<"Electrolyte temperature less than 0K!"<<std::endl;
		exit(0);
	}
	return dif;
}

double dif_Li_sln2_R2(double x, double T, int is)
{
	// Modified based on dif_Li_sln2, introducing Activation Energy
	double dif;
	const double xmin = 0e0;
	const double xmax = 5e3;
	const double Tmin = 253.15e0-10e0-10e0;//Modified to account for -30 oC case
	const double Tmax = 353.15e0;//modified on 08/03/2016 to increase from 80oC to 100 oC
	const double Tg0 = 229e0;
	const double Tg1 = 5e0;
	
	const double Tref = 298.15e0;
	const double Eact = 26e3-8e3+40e3;
	if(!is) T = 298.15;
	if(T>=Tmin && T<=Tmax)
	{
		if(x>=xmin && x<=xmax)
		{
			x *= 1e-3;		// from mol/m3 to mol/L
			dif = -4.43e0 - 54e0/(Tref - Tg0 - x*Tg1) + (-0.22e0)*x; // diffusivity at Tref
			dif = exp(dif*log(10e0));
			dif *= exp(Eact/ugc*(1e0/Tref-1e0/T));
			dif *= 1e-4;		// from cm2/s to m2/s
		}
		else if(x>=0e0 && x<xmin)
			dif = dif_Li_sln2(xmin, T, is);
		else if(x>xmax)
			dif = dif_Li_sln2(xmax, T, is);
		else
		{
			std::cout<<"Electrolyte concentration less than 0!"<<std::endl;
			exit(0);
		}
	}
	else if(T>=0e0 && T<Tmin)
		dif = dif_Li_sln2_R2(x, Tmin, 1);
	else if(T>Tmax)
		dif = dif_Li_sln2_R2(x, Tmax, 1);
	else
	{
		std::cout<<"Electrolyte temperature less than 0K!"<<std::endl;
		exit(0);
	}
	return dif;
}

double dif_EC_sln2(double x, double T, int is)	//Key parameter in degradation
{
	// Safari et al, JES, 156, A145, 2009
	const double dif_ref = 2.0e-18;
	// diffusion limited 5e-17;
	// mixed 1e-16;
	// kinetics limited 1e-14;
	const double Tref = 298.15e0;	
	const double Eact = 50e3;		// ?
	double dif = dif_ref*exp(Eact/ugc*(1e0/Tref - 1e0/T));
	return dif;///10/2;
}

double i0_LI(double x, double ce, double T, int is, double afa, double afc)
{
	if(x>1e-2)return 1e2;
	else return 1e-2;
}

double i0_MCMB_1(double xstoich, double ce, double T, int is, double afa, double afc)
{
	double ecdA_;
    int i;
    double t1,t2,o1,o2;

	const double Eact = 3e4;			// Activation energy for exchange current density at anode

    const double ecda_soc[21]=
    {
        0.0,  0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45,
        0.5,  0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95,
        1.0
    };	

    const double ecda_ref[21]=
    {
        0.0045,  0.007989,  0.010997, 0.013089, 0.014663, 0.015873, 0.016798, 0.017484, 0.017958, 0.018237,
        0.018329,0.018237,  0.017958, 0.017484, 0.016798, 0.015873, 0.014663, 0.013089, 0.010997, 0.007989,
        0.0045
    };

    if(xstoich<0e0) xstoich=1.e-8;
    if(xstoich>1e0) xstoich=1e0-1.e-8;

    i=0;
    while(xstoich>ecda_soc[i]) i++;
    	  
    t1=ecda_soc[i];
    t2=ecda_soc[i-1];
    o1=ecda_ref[i];
    o2=ecda_ref[i-1];
    ecdA_=(o1-o2)/(t1-t2)*(xstoich-t1)+o1;
    ecdA_ *= 0.1;   

	if(is)ecdA_ *= exp(Eact/ugc*(1/T0-1/T)); // for thermal coupled model
    return ecdA_*1e4;
}

double i0_MCMB_2(double xstoich, double ce, double T, int is, double afa, double afc)
{
	// M. Doyle, J. Electrochem. Soc., 150, A706, 2003
	return 26e0;
}

double i0_MCMB_3(double x, double ce, double T, int is, double afa, double afc)
{
	const double k = 1.764e-11;	// m2.5mol-0.5s-1
	double i0 = k;
	return i0;
}

double i0_MCMB_4(double x, double ce, double T, int is, double afa, double afc)
{
	// modified from i0_MCMB_1
	double i0, csmax;
	csmax = mdata[ACT][MCMB].density/mdata[ACT][MCMB].Mw;
	const double Eact = 68e3;//92e3 - 24e3; //13e4;
	const double Tref = 298.15;
	double i0ref = 6e0; //28.76e0;
	double k0ref = 3.46e-11*2*2*2*2; //3.46e-10;
	
	if(!is) T = T0;
	//i0 = i0ref*exp(Eact/ugc*(1e0/Tref - 1e0/T));
	k0ref = i0ref/(faraday*csmax*pow(ce0, afa)*0.5e0);
	//i0 = k0ref*exp(Eact/ugc*(1e0/Tref - 1e0/T))*faraday*csmax*pow(ce0, afaC)*0.5e0;
	if(x>=0e0 && x<=1e0)i0 = k0ref*exp(Eact/ugc*(1e0/Tref - 1e0/T))*faraday*csmax*pow(ce, afa)*pow(x,afc)*pow(1e0-x,afa);
	else i0 = 28e-3;
	return i0;
}

double i0_LTO(double x, double ce, double T, int is, double afa, double afc)
{
	// unknown ??
	double i0, csmax;
	csmax = mdata[ACT][LTO].density/mdata[ACT][LTO].Mw;
	const double Eact = 42e3; //??
	const double Tref = 298.15;
	double i0ref = 1e0; //??
	double k0ref;
	
	if(!is) T = T0;
	k0ref = i0ref/(faraday*csmax*pow(ce0, afa)*0.5e0);
	if(x>=0e0 && x<=1e0)i0 = k0ref*exp(Eact/ugc*(1e0/Tref - 1e0/T))*faraday*csmax*pow(ce, afa)*pow(x,afc)*pow(1e0-x,afa);
	else i0 = 0e0; //i0ref*0.1e0;
	return i0;
}

double i0_LCO(double x, double ce, double T, int is, double afa, double afc)
{
	// M. Doyle, J. Electrochem. Soc., 150, A706, 2003
	// return 36e0;
	return 3.6e0; // use 36*0.1 here
}


double i0_LMO_1(double x, double ce, double T, int is, double afa, double afc)
{
	// M. Doyle, J. Electrochem. Soc., 150, A706, 2003
	return 2e0;
}

double i0_LMO_2(double x, double ce, double T, int is, double afa, double afc)
{
	// T. Fuller .etc, J. Electrochem. Soc., 141, 1, 1994
	return 2.89e0;
}

double i0_LMO_3(double x, double ce, double T, int is, double afa, double afc)
{
	// M. Doyle, J. Newman, J. Electrochem. Soc., 143, 1890, 1996
	return 0.8e0;
}

double i0_LMO_4(double x, double ce, double T, int is, double afa, double afc)
{
	// P. Arora, .etc, J. Power Sources, 88, 219, 2000
	return 4.16e0;	
}

double i0_LMO_5(double x, double ce, double T, int is, double afa, double afc)
{
	// unknown
	double i0, csmax;
	csmax = mdata[ACT][LMO].density/mdata[ACT][LMO].Mw;
	const double Eact = 52e3;
	const double Tref = 298.15;
	double i0ref = 2e0;
	double k0ref;
	
	if(!is) T = T0;
	k0ref = i0ref/(faraday*csmax*pow(ce0, afa)*0.5e0);
	if(x>=0e0 && x<=1e0)i0 = k0ref*exp(Eact/ugc*(1e0/Tref - 1e0/T))*faraday*csmax*pow(ce, afa)*pow(x,afc)*pow(1e0-x,afa);
	else i0 = 0e0;
	return i0;
}

double i0_LNCM(double x, double ce, double T, int is, double afa, double afc)
{
	// unknown
	double i0, csmax;
	csmax = mdata[ACT][NCM].density/mdata[ACT][NCM].Mw;
	const double Eact = 43e3+15e3-6e3; //13e4; //6.83e4;
	const double Tref = 298.15;
	double i0ref = 2e0*0.5; 
	double k0ref = 1.15e-11*2;
	
	if(!is) T = T0;
	//i0 = i0ref*exp(Eact/ugc*(1e0/Tref - 1e0/T));
	k0ref = i0ref/(faraday*csmax*pow(ce0, afa)*0.5e0);
	//i0 = k0ref*exp(Eact/ugc*(1e0/Tref - 1e0/T))*faraday*csmax*pow(ce0, afaC)*0.5e0;
	if(x>=0e0 && x<=1e0)i0 = k0ref*exp(Eact/ugc*(1e0/Tref - 1e0/T))*faraday*csmax*pow(ce, afa)*pow(x,afc)*pow(1e0-x,afa);
	else i0 = 0e0;
	return i0;
}

double i0_LNCM622_1(double x, double ce, double T, int is, double afa, double afc)
{
	// Fitting Equations by Yongjun from ECEC, two-equation

	double i0;
	double coe;
	double ce1;

	ce1 = ce0/1000.0;

	coe = 6.4674+1.3102*log10(x)+2.3262*log10(1.0-x)+0.1527*log10(ce1)-2.8159*1000/T;

/*	if(ce1 <= 1.0)
		coe = 6.4674+1.3102*log10(x)+2.3262*log10(1.0-x)+0.1527*log10(ce1)-2.8159*1000/T;
	else

		coe = 9.3477+2.7724*log10(x)+3.2615*log10(1.0-x)-1.9400*log10(ce1)-3.3063*1000/T;
*/
	i0 = pow(10,coe);	// in A cm-2
	i0 *= 1.0e4;		// convert to A m-2

	i0*=5.0;
	return i0;
}

double i0_LNCM622_2(double x, double ce, double T, int is, double afa, double afc)
{
	// unknown; from NCM111
	double i0, csmax;
	csmax = mdata[ACT][NCM622].density/mdata[ACT][NCM622].Mw;
	const double Eact = 50e3;
	const double Tref = 298.15;
	double i0ref = 1.1e0*5.0; //15e0;
	double k0ref;
		
	if(!is) T = 298.15;
	k0ref = i0ref/(faraday*csmax*pow(ce0, afa)*0.5e0);

	if(x>=0e0 && x<=1e0)
		i0 = k0ref*exp(Eact/ugc*(1e0/Tref - 1e0/T))*faraday*csmax*pow(ce, afa)*pow(x,afc)*pow(1e0-x,afa);
	else 
		i0 = 0e0;
	return i0;
}

double i0_LFPO_1(double ystoich, double ce, double T, int is, double afa, double afc)
{
	// General Motors
	double ecdC_;
    int i;

    double t1,t2,o1,o2;

	const double Eact = 3e4;			// Activation energy for exchange current density at cathode

    const double ecdc_soc[9]=
    {
        0.0, 0.449959, 0.567431, 0.684903, 0.802375, 0.86111, 0.890478, 0.919846, 1.0
    };

    const double ecdc_ref[9]=
    {
	      2e-4, 1.45e-04, 1.21e-04, 8.41e-05, 3.28e-05, 6.31e-06, 4.23e-06, 3.35e-06, 3.2e-6
    };

    if(ystoich<0e0) ystoich=1.e-8;
    if(ystoich>1e0) ystoich=1e0-1.e-8;

    i=0;
    while(ystoich>ecdc_soc[i]) i++;

    t1=ecdc_soc[i];
    t2=ecdc_soc[i-1];
    o1=ecdc_ref[i];
    o2=ecdc_ref[i-1];
    ecdC_=(o1-o2)/(t1-t2)*(ystoich-t1)+o1;
	ecdC_=ecdC_*1.5; 

    if(is)ecdC_ *= exp(Eact/ugc*(1/T0-1/T)); //for thermal coupled model
    return ecdC_*1e4;
}

double i0_LFPO_2(double x, double ce, double T, int is, double afa, double afc)
{
	// V. Srinivasan .etc, J. Electrochem. Soc., 151, A1517, 2004
	// should be 3.14e-6A/cm2 in the literature
	double i0, csmax;
	csmax = mdata[ACT][LFP].density/mdata[ACT][LFP].Mw;
	const double Eact = 30e3; //??
	const double Tref = 298.15;
	double i0ref = 3.14e-2;	// 50% soc
	double k0ref;
	
	if(!is) T = T0;
	k0ref = i0ref/(faraday*csmax*pow(ce0, afa)*0.5e0);
	i0 = k0ref*exp(Eact/ugc*(1e0/Tref - 1e0/T))*faraday*csmax*pow(ce, afa)*pow(x,afc)*pow(1e0-x,afa);
	return i0;
}

double i0_FGR(double x, double cec, double T, int is, double af, double add)
{
	const double k0ref = 1e-10;	// 0.6e-12[m/s]
	// kinetics limited 0.8e-10
	// mixed 1e-10
	// diffusion limited 1e-8
	const double Eact = 43e3*0.6;//42.733e3; //50e3;
	const double Tref = 298.15e0;
	double i0ref = faraday*k0ref*cec;
	if(!is) T = T0;
	double i0 = i0ref*exp(Eact/ugc*(1e0/Tref - 1e0/T));
	return i0/20*0.7*0.5;//i0/200;
}

double k0_FGR(double T, int is)
{
	const double k0ref = 2.0e-12;	//[m/s]
	const double Eact = 50e3;//43e3*0.6;
	const double Tref = 298.15e0;
	if(!is) T = T0;
	double k0 = k0ref*exp(Eact/ugc*(1e0/Tref - 1e0/T));
	return k0;//Original: k0/20*0.7*0.5/4.5*0.75;
}

double i0_FNCM(double x, double cec, double T, int is, double af, double add)
{
	const double k0ref = 2e-7;//0.6e-12;//*1e3;		//[m/s]
	const double Eact = 42.733e3*0.6; //50e3;
	const double Tref = 298.15e0;
	if(!is) T = T0;
//	double frt = faraday/(ugc*T);
	double i0 = k0ref*exp(Eact/ugc*(1e0/Tref - 1e0/T));
	return i0*0.866*0.8;//*0.933;//*0.866;//i0;
}

double k0_FNCM(double T, int is)
{
	const double k0ref = 6.16e-9/4;	//[m/s]
	const double Eact = 42.733e3*0.6; //50e3;
	const double Tref = 298.15e0;
	if(!is) T = T0;
	return k0ref*exp(Eact/ugc*(1e0/Tref - 1e0/T));
}

double i0_FLMO(double x, double cec, double T, int is, double af, double add)
{
	const double k0ref = 0e0;//2e-7;		//[m/s]
	const double Eact = 42.733e3*0.6; //50e3;
	const double Tref = 298.15e0;
	if(!is) T = T0;
//	double frt = faraday/(ugc*T);
	double i0 = k0ref*exp(Eact/ugc*(1e0/Tref - 1e0/T));
	return i0*0.866*0e0;//*0.933;//*0.866;//i0;
}

double k0_FLMO(double T, int is)
{
	const double k0ref = 0e0;//2e-7;	//[m/s]
	const double Eact = 42.733e3*0.6; //50e3;
	const double Tref = 298.15e0;
	if(!is) T = T0;
	return k0ref*exp(Eact/ugc*(1e0/Tref - 1e0/T))*0.866*0e0;
}

double dUdT_MCMB_1(double x)
{
	double dUdT;
	double xmin = 0e0;
	double xmax = 0.8e0;
	if(x>=xmin && x<=xmax)
	{
		double x2 = x*x;
		double x3 = x2*x;
		double x4 = x3*x;
		double x5 = x4*x;
		double x6 = x5*x;
		double x7 = x6*x;
		double x8 = x7*x;
		dUdT = (0.00527e0 + 3.29927e0*x - 91.79326e0*x2 + 1004.91101e0*x3 - 5812.27813e0*x4
			+ 19329.75490e0*x5 - 37147.89470e0*x6 + 38379.18127e0*x7 - 16515.05308e0*x8)/
			(1e0 - 48.09287e0*x + 1017.23480e0*x2 - 10481.80419e0*x3 + 59431.30001e0*x4
			- 195881.64880e0*x5 + 374577.31520e0*x6 - 385821.16070e0*x7 + 165705.85970e0*x8)*1e-3;
	}
	else if(x>=0e0 && x<xmin)
		dUdT = dUdT_MCMB_1(xmin);
	else if(x>xmax && x<=1e0)
		dUdT = dUdT_MCMB_1(xmax);
	else
	{
		std::cout<<"Anode Stoich out of range!"<<std::endl;
		exit(0);
	}
	return dUdT;
}

double dUdT_MCMB_2(double x)
{
    double dudt_a = 0e0;
    dudt_a = 344.1347148*exp(-32.9633287*x+8.316711484)/(1+749.0756003*exp(-34.79099646*x+8.887143624))
		-0.8520278805*x+0.362299229*pow(x,2)+0.2698001697;
    dudt_a = dudt_a*1e-3;
    return dudt_a;
}

double dUdT_MCMB_3(double x)
{
	// Y. F. Reynier, J. Electrochem. Soc., 151, A422, 2004
	int icount = 0;
	int nmid;
	int nmin = 0;
	int nmax = sizeof(x_dUdT_MCMB_3)/sizeof(double) - 1;
	double U;
	const double xmin = x_dUdT_MCMB_3[nmin];
	const double xmax = x_dUdT_MCMB_3[nmax];
	if(x>=xmin && x<=xmax)
	{
		while(nmax - nmin>1)
		{
			nmid = (nmin + nmax)/2;
			if(x>x_dUdT_MCMB_3[nmid] && x<x_dUdT_MCMB_3[nmax]) nmin = nmid;
			else if(x>x_dUdT_MCMB_3[nmin] && x<x_dUdT_MCMB_3[nmid]) nmax = nmid;
			else if(x==x_dUdT_MCMB_3[nmin]) return y_dUdT_MCMB_3[nmin]/faraday;
			else if(x==x_dUdT_MCMB_3[nmid]) return y_dUdT_MCMB_3[nmid]/faraday;
			else if(x==x_dUdT_MCMB_3[nmax]) return y_dUdT_MCMB_3[nmax]/faraday;
			icount ++;
		}
		U = y_dUdT_MCMB_3[nmin] + (x - x_dUdT_MCMB_3[nmin])/(x_dUdT_MCMB_3[nmax] - x_dUdT_MCMB_3[nmin])
			*(y_dUdT_MCMB_3[nmax] - y_dUdT_MCMB_3[nmin]);
		return U/faraday;
	}
	else if(x>=0e0 && x<xmin)
		U = dUdT_MCMB_3(xmin);
	else if(x>xmax) // && x<=1e0)
		U = dUdT_MCMB_3(xmax);
	else
	{
		std::cout<<"Anode Stoich out of range! dUdT"<<std::endl;
		exit(0);
	}
	return U;
};

double dUdT_LCO(double x)
{
	double dUdT;
	double xmin = 0.46e0;
	double xmax = 1e0;
	if(x>=xmin && x<=xmax)
	{
		double x2 = x*x;
		double x3 = x2*x;
		double x4 = x3*x;
		dUdT = (-0.19952e0 + 0.92837e0*x - 1.36455e0*x2 + 0.61154e0*x3)*1e-3
			/(1e0 - 5.66148e0*x + 11.47636e0*x2 - 9.82431e0*x3 + 3.04876e0*x4);
	}
	else if(x>=0e0 && x<xmin)
		dUdT = dUdT_LCO(xmin);
	else if(x>xmax && x<=1e0)
		dUdT = dUdT_LCO(xmax);
	else
	{
		std::cout<<"Cathode Stoich out of range!"<<std::endl;
		exit(0);
	}
	return dUdT;
}

double dUdT_LMO(double x)
{
	// V. Srinivasan, C. Y. Wang, J. Electrochem. Soc., 150, A98, 2003
	double dUdT;
	double xmin = 0.17e0;
	double xmax = 1e0;
	if(x>=xmin && x<=xmax)
	{
		dUdT = 4.31274309e0*exp(0.571536523e0*x) + 1.281681122e0*sin(-4.9916739e0*x)
			- 0.090453431e0*sin(-20.9669665e0*x + 12.5788250e0) 
			- 0.0313472974e0*sin(31.7663338e0*x - 22.4295664e0) - 4.14532933e0
			+ 8.147113434e0*x - 26.064581e0*x*x + 12.7660158e0*x*x*x
			- 0.184274863e0*exp(-(x - 0.5169435168e0)*(x - 0.5169435168e0)/0.04628266783e0);
		dUdT *= 1e-3;
	}
	else if(x>=0e0 && x<xmin)
		dUdT = dUdT_LMO(xmin);
	else if(x>xmax && x<=1e0)
		dUdT = dUdT_LMO(xmax);
	else
	{
		std::cout<<"Cathode Stoich out of range!"<<std::endl;
		exit(0);
	}
	return dUdT;
}

double dUdT_LNCM_1(double y)
{
	// Fang's code
    double dudt_c = 0e0;
    if(y<0.4){dudt_c=0.4-y;}
    else if(y<0.5){dudt_c=-3.0*(y-0.4);}
    else if(y<0.7){dudt_c=-0.3+(y-0.5)*2.5;}
    else if(y<=1.0){dudt_c=0.2-(y-0.7)*5.0/3.0;}
    dudt_c=dudt_c*0.2e-3;
	return dudt_c;
}

double dUdT_LNCM_2(double x)
{
	// W. Lu, J. Electrochem. Soc., 153, A2147, 2006
	int icount = 0;
	int nmid;
	int nmin = 0;
	int nmax = sizeof(x_dUdT_LNCM_2)/sizeof(double) - 1;
	double U;
	const double xmin = x_dUdT_LNCM_2[nmin];
	const double xmax = x_dUdT_LNCM_2[nmax];
	if(x>=xmin && x<=xmax)
	{
		while(nmax - nmin>1)
		{
			nmid = (nmin + nmax)/2;
			if(x>x_dUdT_LNCM_2[nmid] && x<x_dUdT_LNCM_2[nmax]) nmin = nmid;
			else if(x>x_dUdT_LNCM_2[nmin] && x<x_dUdT_LNCM_2[nmid]) nmax = nmid;
			else if(x==x_dUdT_LNCM_2[nmin]) return y_dUdT_LNCM_2[nmin]*1e-3;
			else if(x==x_dUdT_LNCM_2[nmid]) return y_dUdT_LNCM_2[nmid]*1e-3;
			else if(x==x_dUdT_LNCM_2[nmax]) return y_dUdT_LNCM_2[nmax]*1e-3;
			icount ++;
		}
		U = y_dUdT_LNCM_2[nmin] + (x - x_dUdT_LNCM_2[nmin])/(x_dUdT_LNCM_2[nmax] - x_dUdT_LNCM_2[nmin])
			*(y_dUdT_LNCM_2[nmax] - y_dUdT_LNCM_2[nmin]);
		return U*1e-3;
	}
	else if(x>=0e0 && x<xmin)
		U = dUdT_LNCM_2(xmin);
	else if(x>xmax && x<=1e0)
		U = dUdT_LNCM_2(xmax);
	else
	{
		std::cout<<"Cathode Stoich out of range!"<<std::endl;
		exit(0);
	}
	return U;
};

double dUdT_LI(double x)
{
	return 0e0;
}

double dlnfdlnc_sln1(double x, double T, int is)
{
	return 0e0;
}

double dlnfdlnc_sln2(double x, double T, int is)
{
	// LiPF6 in PC(10%)-EC(27%)-DMC(63%)
	// L Valoen & J Reimers, J. Electrochem. Soc., 152, A882, 2005
	double dlnfdlnc;
	const double xmin = 0e0;
	const double xmax = 5e3;
	const double Tmin = 233.15e0;
	const double Tmax = 353.15e0;
	if(!is) T = T0;
	if(T>=Tmin && T<=Tmax)
	{
		if(x>=xmin && x<=xmax)
		{
			x *= 1e-3;		// from mol/m3 to mol/L
			dlnfdlnc = 0.601e0 -0.24e0*sqrt(x) + (0.982e0*(1 - 0.0052e0*(T - 293.15e0)))*x*sqrt(x);
			dlnfdlnc = (dlnfdlnc/0.601e0) - 1e0;
		}
		else if(x>=0e0 && x<xmin)
			dlnfdlnc = dlnfdlnc_sln2(xmin, T, is);
		else if(x>xmax)
			dlnfdlnc = dlnfdlnc_sln2(xmax, T, is);
		else
		{
			std::cout<<"Electrolyte concentration less than 0!"<<std::endl;
			exit(0);
		}
	}
	else if(T>=0e0 && T<Tmin)
		dlnfdlnc = dlnfdlnc_sln2(x, Tmin, 1);
	else if(T>Tmax)
		dlnfdlnc = dlnfdlnc_sln2(x, Tmax, 1);
	else
	{
		std::cout<<"Electrolyte temperature less than 0K!"<<std::endl;
		exit(0);
	}
	return dlnfdlnc*2.5;
}

double dedt_MCMB(double x, double T, int is)
{
	//const double dedt0 = 1.02e-12/360/5.375e-6*4;

	const double dedt0 = 1.0e-20;
	const double Tref = 298.15e0;
	const double Eact = 50e3*0.6;
	if(!is) T = T0;
	double dedt = dedt0*exp(Eact/ugc*(1e0/Tref - 1e0/T));
	return dedt;
}

double dedt_LMO(double x, double T, int is)
{
	const double dedt0 = 1.02e-12/360*0.95;
	const double Tref = 298.15e0;
	const double Eact = 50e3;
	if(!is) T = T0;
	//double dedt = dedt0*exp(Eact/ugc*(1e0/Tref - 1e0/T));
	return 0e0;//dedt;
}

double dedt_LNCM(double x, double T, int is)
{
	const double dedt0 = 1.02e-12/360*0.95;
	const double Tref = 298.15e0;
	const double Eact = 50e3;
	if(!is) T = T0;
	double dedt = dedt0*exp(Eact/ugc*(1e0/Tref - 1e0/T));
	return dedt*0e0;
}

double dedt_LFP(double x, double T, int is)
{
	const double dedt0 = 1e-11;
	const double Tref = 298.15e0;
	const double Eact = 50e3;
	if(!is) T = T0;
	double dedt = dedt0*exp(Eact/ugc*(1e0/Tref - 1e0/T));
	return dedt*0e0;
}


double NCM622_Ds_T60_MLinear_1(double xc, double dif_cutoff)
{
	double diff;
	if (xc < 0.8)
		diff = 1.0e-11*(6.1755-3.5132*xc);	
	else	
		diff = 3.36494e-11+(dif_cutoff-3.36494e-11)/0.2*(xc-0.8);

	return diff;
}
double NCM622_Ds_T40_MLinear_1(double xc, double dif_cutoff)
{
	double diff;
	if (xc < 0.8)
		diff = 1.0e-11*(6.58003-4.36936*xc);
	else
		diff = 3.084542e-11+(dif_cutoff-3.084542e-11)/0.2*(xc-0.8);

	return diff;
}
double NCM622_Ds_T20_MLinear_1(double xc, double dif_cutoff)
{
	double diff;
	if (xc < 0.8)
		diff = 1.0e-11*(6.63556-5.3742*xc);
	else
		diff = 2.3362e-11+(dif_cutoff-2.3362e-11)/0.2*(xc-0.8);

	return diff;
}
double NCM622_Ds_T00_MLinear_1(double xc, double dif_cutoff)
{
	double diff;
	if (xc < 0.5)
		diff = 1.0e-11*(4.26414-1.80082*xc);
	else if(xc<0.7)
		diff = 1.0e-11*(8.44492-10.3171*xc);
	else
		diff = 1.22295e-11+(dif_cutoff-1.22295e-11)/0.3*(xc-0.7);

	return diff;
}
double NCM622_Ds_TM15_MLinear_1(double xc, double dif_cutoff)
{
	double diff;
	if (xc < 0.5)
		diff = 1.0e-11*(3.85883-3.04422*xc);
	else if(xc < 0.6)
		diff = 1.0e-11*(9.22379-13.7242*xc);
	else
		diff = 0.98927e-11+(dif_cutoff-0.98927e-11)/0.4*(xc-0.6);

	return diff;
}
double NCM622_Ds_TM30_MLinear_1(double xc, double dif_cutoff)
{
	double diff;
	if (xc < 0.45)
		diff = 1.1155e-11;
	else if(xc < 0.55)
		diff = 1.0e-11*(3.92775-6.21431*xc);
	else
		diff = 5.0e-12;

	return diff;
}
double NCM622_interpolation(double xc, double x1, double x2, double y1, double y2)
{
	double yc;//returned value 
	
	if (x1==x2)
		yc = y1;
	else
		yc = y1 + (y2-y1)*(xc-x1)/(x2-x1);
	
	return yc;
}