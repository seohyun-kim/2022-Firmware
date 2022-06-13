## 2022-04-11

![image](https://user-images.githubusercontent.com/61939286/173378755-a06e5efe-3f80-4d6e-9971-58245240c429.png)  

![image](https://user-images.githubusercontent.com/61939286/173378785-a740cd2c-763e-4ddd-a22f-aa928d7f80b8.png)  

![image](https://user-images.githubusercontent.com/61939286/173378812-79f91b1f-0536-44c2-835b-e51990795d69.png)  

![image](https://user-images.githubusercontent.com/61939286/173378826-fc6b5ec3-a20b-4004-8304-b36e99c32588.png)  

![image](https://user-images.githubusercontent.com/61939286/173378893-3cc12d43-ded7-447c-8e7b-eb621f420708.png)  

![image](https://user-images.githubusercontent.com/61939286/173379029-6a47698f-2102-4aac-b992-f953f25547c5.png)  

![image](https://user-images.githubusercontent.com/61939286/173379051-08d96c32-522b-429a-8a89-f92bda307656.png)  

```c
void MyApp()
{
 // My Code
	*((V_UINT32*)(0x40023830U)) |= 0x00000040U; // [Offset : 0x30] GPIOG EN를 Clock Enable(01)로 설정 (6번비트)
	*((V_UINT32*)(0x40021800U)) |= 0x01000000U; //[offser: 0x00] MODER12를 output 모드(01)을 설정
	*((V_UINT32*)(0x40021808U)) |= 0x03000000U; //[offset: 0x08] OSPEEDR를 veryhigh(11)로 설정
	*((V_UINT32*)(0x4002180cU)) |= 0x01000000U; //[offser: 0xoc] PUPDR를 pull up(01)을 설정
	*((V_UINT32*)(0x40021818U)) |= 0x10000000U; //[offser: 0x18] BSRR을 reset

}
```

![image](https://user-images.githubusercontent.com/61939286/173379131-1a5f007c-5dec-40c3-a7e3-98eb3bb20fb5.png)
