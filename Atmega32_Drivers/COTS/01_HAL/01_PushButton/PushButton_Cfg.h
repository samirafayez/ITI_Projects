#ifndef PushButton_Cfg_H
#define PushButton_Cfg_H



#define PushButton_PULL_UP 0
#define PushButton_PULL_DOWN 1



typedef struct{
	u8 PushButton_InputStatus;
}PushButton_tstrPinCfg_t;


const PushButton_tstrPinCfg_t PushButton_strPinCfg[32]= {
	/*Pin0*/{PushButton_PULL_UP},
	/*Pin1*/{PushButton_PULL_UP},
	/*Pin2*/{PushButton_PULL_UP},
	/*Pin3*/{PushButton_PULL_UP},
	/*Pin4*/{PushButton_PULL_UP},
	/*Pin5*/{PushButton_PULL_UP},
	/*Pin6*/{PushButton_PULL_UP},
	/*Pin7*/{PushButton_PULL_UP},
	/*Pin8*/{PushButton_PULL_UP},
	/*Pin9*/{PushButton_PULL_UP},
	/*Pin10*/{PushButton_PULL_UP},
	/*Pin11*/{PushButton_PULL_UP},
	/*Pin12*/{PushButton_PULL_UP},
	/*Pin13*/{PushButton_PULL_UP},
	/*Pin14*/{PushButton_PULL_UP},
	/*Pin15*/{PushButton_PULL_UP},
	/*Pin16*/{PushButton_PULL_UP},
	/*Pin17*/{PushButton_PULL_UP},
	/*Pin18*/{PushButton_PULL_UP},
	/*Pin19*/{PushButton_PULL_UP},
	/*Pin20*/{PushButton_PULL_UP},
	/*Pin21*/{PushButton_PULL_UP},
	/*Pin22*/{PushButton_PULL_UP},
	/*Pin23*/{PushButton_PULL_UP},
	/*Pin24*/{PushButton_PULL_UP},
	/*Pin25*/{PushButton_PULL_UP},
	/*Pin26*/{PushButton_PULL_UP},
	/*Pin27*/{PushButton_PULL_UP},
	/*Pin28*/{PushButton_PULL_UP},
	/*Pin29*/{PushButton_PULL_UP},
	/*Pin30*/{PushButton_PULL_UP},
	/*Pin31*/{PushButton_PULL_UP}
	
	};

#endif /*PushButton_Cfg_H*/