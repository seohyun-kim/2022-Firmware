# 버튼 1을 세팅하고, 눌렀을 때 LED켜지도록 하기  

![image](https://user-images.githubusercontent.com/61939286/173381036-b4beab00-8eb9-4db8-a5f3-163b745c72b6.png)

![image](https://user-images.githubusercontent.com/61939286/173381054-0bf3935a-db14-4440-8c9f-4bb9fd006e20.png)

![image](https://user-images.githubusercontent.com/61939286/173381072-038fe1db-a6e2-4886-94fe-81a03ea26b4f.png)

- 스위치 누르지 않으면 0 누르면 1
- 캐패시터는 일부 AC성분 빼내는 역할, 용량 안정화 (아날로그적 역할임)

![image](https://user-images.githubusercontent.com/61939286/173381254-924dc519-f5a5-4ed8-a52d-21837cb0510f.png)

![image](https://user-images.githubusercontent.com/61939286/173381297-b57024df-ac1a-400f-ab5d-6885c0efce9d.png)

![image](https://user-images.githubusercontent.com/61939286/173381338-08b8e804-3129-4cee-b56b-4b73d5dbf878.png)

![image](https://user-images.githubusercontent.com/61939286/166206020-22f5cb46-8227-4265-ab61-fb0fd67a95c6.png)


```c
void MyApp()
{

	InitGPIO(); // LED 4개 관련 클럭 모두 Enable, 모두 OFF로 초기화

	SetOneButton(1); // 버튼 세팅
	SetOneLED(1); // LED 1번 세팅

	while(1){
		if((GetIDRforButton(1) >> getPortforButton(1)) == 1){ // 버튼 클릭 시
			TurnOnOneLED(1);
		}else{
			TurnOffOneLED(1);
		}
	}
}
```

```c
void SetOneButton(UINT32 No){
	//MODER INPUTMODE
	*((V_UINT32*)(getBaseAddrforButton(No)+MODEROFFSET))  &= ~(AndMaskforTwoBit << (getPortforButton(No)*2)); // 해당 2bit를 00으로 초기화
	*((V_UINT32*)(getBaseAddrforButton(No)+MODEROFFSET))  |=  (INPUTMODE        << (getPortforButton(No)*2)); // 원하는 값을 덮어 씀

	//OSPEED VERY HIGH
	*((V_UINT32*)(getBaseAddrforButton(No)+OSPEEDOFFSET))	&= ~(AndMaskforTwoBit << (getPortforButton(No)*2)); // 해당 2bit를 00으로 초기화
	*((V_UINT32*)(getBaseAddrforButton(No)+OSPEEDOFFSET)) |=  (LOWSPEED         << (getPortforButton(No)*2)); // 원하는 값을 덮어 씀

	//PUPDR PULL UP
	*((V_UINT32*)(getBaseAddrforButton(No)+PUPDROFFSET))  &= ~(AndMaskforTwoBit << (getPortforButton(No)*2)); // 해당 2bit를 00으로 초기화
	*((V_UINT32*)(getBaseAddrforButton(No)+PUPDROFFSET))  |=  (NOPUPD           << (getPortforButton(No)*2)); // 원하는 값을 덮어 씀
}

UINT32 GetIDRforButton(UINT32 ButtonNo){
	return (*((V_UINT32*)(getBaseAddrforButton(ButtonNo)+IDROFFSET))) & (0x00000001U << getPortforButton(ButtonNo));
}

```

```c
void TurnOnOneLED(UINT32 No){ // NO 는 1~4 사이의 정수
	SetOneLED(No);
	// BSRR reset
	*((V_UINT32*)(getBaseAddrforLED(No)+BSRROFFSET))  |= (SETRESET << (getPortforLED(No)+16));
}

void TurnOffOneLED(UINT32 No){ // NO 는 1~4 사이의 정수
	// BSRR set
	SetOneLED(No);
	*((V_UINT32*)(getBaseAddrforLED(No)+BSRROFFSET))  |= (SETRESET << getPortforLED(No));
}

void SetOneLED(UINT32 No){
	//MODER OUTPUTMODE
	*((V_UINT32*)(getBaseAddrforLED(No)+MODEROFFSET))  &= ~(AndMaskforTwoBit << (getPortforLED(No)*2)); // 해당 2bit를 00으로 초기화
	*((V_UINT32*)(getBaseAddrforLED(No)+MODEROFFSET))  |=  (OUTPUTMODE       << (getPortforLED(No)*2)); // 원하는 값을 덮어 씀

	//OSPEED VERY HIGH
	*((V_UINT32*)(getBaseAddrforLED(No)+OSPEEDOFFSET)) &= ~(AndMaskforTwoBit << (getPortforLED(No)*2)); // 해당 2bit를 00으로 초기화
	*((V_UINT32*)(getBaseAddrforLED(No)+OSPEEDOFFSET)) |=  (VERYHIGHSPEED    << (getPortforLED(No)*2)); // 원하는 값을 덮어 씀

	//PUPDR PULL UP
	*((V_UINT32*)(getBaseAddrforLED(No)+PUPDROFFSET))  &= ~(AndMaskforTwoBit << (getPortforLED(No)*2)); // 해당 2bit를 00으로 초기화
	*((V_UINT32*)(getBaseAddrforLED(No)+PUPDROFFSET))  |=  (PULLUP           << (getPortforLED(No)*2)); // 원하는 값을 덮어 씀
}
```

```c
UINT32 getPortforLED(UINT32 LEDNo){ // LED 1~4
		switch(LEDNo){
			case 1: return 12;
			case 2: return  5;
			case 3: return  4;
			case 4: return 10;
			case 5: return  9; // SYS_STS_LED
		}
}

UINT32 getBaseAddrforButton(UINT32 ButtonNo){ // BTN 1~2
	switch(ButtonNo){
		case 1: return GPIOC_BASEADDRESS;
		case 2: return GPIOG_BASEADDRESS;
	}
}

UINT32 getPortforButton(UINT32 ButtonNo){ // BTN 1~2
		switch(ButtonNo){
			case 1: return 12; // PC 12
			case 2: return 3;  // PG  3
		}
}
```
