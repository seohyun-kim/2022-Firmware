# 내부, 외부 LED 4개씩 제어하기

![image](https://user-images.githubusercontent.com/61939286/168562324-4c2db5bf-3daa-4900-91de-a5475206f512.png)


![image](https://user-images.githubusercontent.com/61939286/168562206-b237b752-1606-4515-9f27-abcd9db11f36.png)


### MyApp()
```c
void MyApp()
{


	InitGPIO(); //G, E, C Enable
	while(1){
		TurnOnOneLEDb(1, 'I', 10);
		TurnOnOneLEDb(2, 'I', 10);
		TurnOnOneLEDb(3, 'I', 10);
		TurnOnOneLEDb(4, 'I', 10);

		TurnOnOneLEDb(1, 'O', 10);
		TurnOnOneLEDb(2, 'O', 10);
		TurnOnOneLEDb(3, 'O', 10);
		TurnOnOneLEDb(4, 'O', 10);

	}

}

```

### TurnOnOneLEDb(UINT32 No, char InOut, UINT32 Duration)
```c
void TurnOnOneLEDb(UINT32 No, char InOut, UINT32 Duration){
	// No = LED번호 (내 외부의 1~4번)
	// InOut = 내부 LED인지(I), 외부 LED인지(O)를 구분
	// Duration = 켜져있는 시간 (100ms단위, 10이면 1초)
	// 지정된 LED이외에는 나머지 모든 LED를 끄도록 함
	//Duration 동안에는 Block시킴

	UINT32 waitingTime = Duration * HUNDREDms;
	TurnOffAllInOutLED(); // 내부 LED 4개, 외부 LED 4개 모두 Off한 상태로 시작

	switch(InOut){
		case 'I': // 내부 LED
			while(waitingTime --){
				TurnOnOneLED(No);
			}
			break;

		case 'O': // 외부 LED
			while(waitingTime --){
				TurnOnOneOutLED(No);
			}
			break;
	}

}
```
