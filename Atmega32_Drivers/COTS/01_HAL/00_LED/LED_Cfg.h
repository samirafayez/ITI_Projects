#ifndef LED_Cfg_H
#define LED_Cfg_H



#define LED_ACTIVE_LOW 0
#define LED_ACTIVE_HIGH 1



typedef struct{
	u8 LED_ActiveStatus;
}LED_tstrPinCfg_t;


const LED_tstrPinCfg_t LED_strPinCfg[32]= {
	/*Pin0*/{LED_ACTIVE_HIGH},
	/*Pin1*/{LED_ACTIVE_HIGH},
	/*Pin2*/{LED_ACTIVE_HIGH},
	/*Pin3*/{LED_ACTIVE_HIGH},
	/*Pin4*/{LED_ACTIVE_HIGH},
	/*Pin5*/{LED_ACTIVE_HIGH},
	/*Pin6*/{LED_ACTIVE_HIGH},
	/*Pin7*/{LED_ACTIVE_HIGH},
	/*Pin8*/{LED_ACTIVE_HIGH},
	/*Pin9*/{LED_ACTIVE_HIGH},
	/*Pin10*/{LED_ACTIVE_HIGH},
	/*Pin11*/{LED_ACTIVE_HIGH},
	/*Pin12*/{LED_ACTIVE_HIGH},
	/*Pin13*/{LED_ACTIVE_HIGH},
	/*Pin14*/{LED_ACTIVE_HIGH},
	/*Pin15*/{LED_ACTIVE_HIGH},
	/*Pin16*/{LED_ACTIVE_HIGH},
	/*Pin17*/{LED_ACTIVE_HIGH},
	/*Pin18*/{LED_ACTIVE_HIGH},
	/*Pin19*/{LED_ACTIVE_HIGH},
	/*Pin20*/{LED_ACTIVE_HIGH},
	/*Pin21*/{LED_ACTIVE_HIGH},
	/*Pin22*/{LED_ACTIVE_HIGH},
	/*Pin23*/{LED_ACTIVE_HIGH},
	/*Pin24*/{LED_ACTIVE_HIGH},
	/*Pin25*/{LED_ACTIVE_HIGH},
	/*Pin26*/{LED_ACTIVE_HIGH},
	/*Pin27*/{LED_ACTIVE_HIGH},
	/*Pin28*/{LED_ACTIVE_HIGH},
	/*Pin29*/{LED_ACTIVE_HIGH},
	/*Pin30*/{LED_ACTIVE_HIGH},
	/*Pin31*/{LED_ACTIVE_HIGH}
	
	};

#endif /*LED_Cfg_H*/