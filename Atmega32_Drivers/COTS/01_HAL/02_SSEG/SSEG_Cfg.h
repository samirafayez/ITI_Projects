/*
 * SSEG_Cfg.h
 *
 * Created: 1/20/2023 2:47:33 PM
 *  Author: HP
 */ 

#ifndef SSEG_CFG_H_
#define SSEG_CFG_H_

#define SSEG_ACTIVE_LOW 0
#define SSEG_ACTIVE_HIGH 1



typedef struct{
	u8 SSEG_ActiveStatus;
}SSEG_tstrPinCfg_t;


const SSEG_tstrPinCfg_t SSEG_strPinCfg[32]= {
	/*Pin0*/{SSEG_ACTIVE_HIGH},
	/*Pin1*/{SSEG_ACTIVE_HIGH},
	/*Pin2*/{SSEG_ACTIVE_HIGH},
	/*Pin3*/{SSEG_ACTIVE_HIGH},
	/*Pin4*/{SSEG_ACTIVE_HIGH},
	/*Pin5*/{SSEG_ACTIVE_HIGH},
	/*Pin6*/{SSEG_ACTIVE_HIGH},
	/*Pin7*/{SSEG_ACTIVE_HIGH},
	/*Pin8*/{SSEG_ACTIVE_HIGH},
	/*Pin9*/{SSEG_ACTIVE_HIGH},
	/*Pin10*/{SSEG_ACTIVE_HIGH},
	/*Pin11*/{SSEG_ACTIVE_HIGH},
	/*Pin12*/{SSEG_ACTIVE_HIGH},
	/*Pin13*/{SSEG_ACTIVE_HIGH},
	/*Pin14*/{SSEG_ACTIVE_HIGH},
	/*Pin15*/{SSEG_ACTIVE_HIGH},
	/*Pin16*/{SSEG_ACTIVE_HIGH},
	/*Pin17*/{SSEG_ACTIVE_HIGH},
	/*Pin18*/{SSEG_ACTIVE_HIGH},
	/*Pin19*/{SSEG_ACTIVE_HIGH},
	/*Pin20*/{SSEG_ACTIVE_HIGH},
	/*Pin21*/{SSEG_ACTIVE_HIGH},
	/*Pin22*/{SSEG_ACTIVE_HIGH},
	/*Pin23*/{SSEG_ACTIVE_HIGH},
	/*Pin24*/{SSEG_ACTIVE_HIGH},
	/*Pin25*/{SSEG_ACTIVE_HIGH},
	/*Pin26*/{SSEG_ACTIVE_HIGH},
	/*Pin27*/{SSEG_ACTIVE_HIGH},
	/*Pin28*/{SSEG_ACTIVE_HIGH},
	/*Pin29*/{SSEG_ACTIVE_HIGH},
	/*Pin30*/{SSEG_ACTIVE_HIGH},
	/*Pin31*/{SSEG_ACTIVE_HIGH}
	
};




#endif /* SSEG_CFG_H_ */