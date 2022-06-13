## 2022-05-09  

![image](https://user-images.githubusercontent.com/61939286/173382157-8662033b-5c25-4f1c-8d8a-75589dcd9db5.png)

![image](https://user-images.githubusercontent.com/61939286/173382177-8f424af3-5d36-4e60-8a58-67b64d616959.png)

![image](https://user-images.githubusercontent.com/61939286/173382209-f919f650-bc42-4941-907b-93c77cab8643.png)

- 서로 상관 관계 없이 독립적
- 버튼을 빠른 순간에 눌렀다가 떼면 이 루프는 수십만번 돌아 갈 것임....


![image](https://user-images.githubusercontent.com/61939286/173382262-5771f35e-5a67-40a8-bd3f-8c55c0ca4631.png)
- 먼저 버튼 체크 (뭐가 눌러졌는지)
    - 넷 중에 하나를 리턴하도록 함
- 그 리턴 값(0~3) 으로 분기

- 입력이 없으면 리턴 되지 않도록 Blocking 시키는 방법,
    
    입력이 있을 때 까지 기다리는 방법
    
    → 이 방법에서 둘다 눌리는 것은 거의 안 넘어옴(물리적 동시가 거의 불가능함)


![image](https://user-images.githubusercontent.com/61939286/173382312-c90bcc01-68b3-4d02-b1f8-beb5de4e3cd7.png)

![image](https://user-images.githubusercontent.com/61939286/173382424-3958ae2c-e438-49f0-94dd-8970525aa40a.png)

![image](https://user-images.githubusercontent.com/61939286/173382450-c2f15dff-f0e9-4b20-8fe6-6c587cda4937.png)

1. Blocking 방식
2. Non-Blocking 방식
3. 시스템 인터럽트 이용

- 셋 중에 뭘 써도 상관 없음

- 10초 동안 버튼이 눌리면 버튼 동작 관련 일 수행하고, 10초 동안 아무 일도 없다면 다른 일을 해라
    - 이런 식으로 프로그래밍을 짠다면, 10초 지나서야 확인 가능..?
    
- `**딜레이`와 `버튼 체크`가 동시에 일어나야 함...!!!!**
    - for문 안에서 버튼 체크가 일어나도록 해야함 (기다리면서 버트 체크)
    - 기다리면서 입력이 있으면 for루프를 빠져나옴

![image](https://user-images.githubusercontent.com/61939286/173382531-7495b6ed-d45a-45c1-b8e2-385709864a57.png)

- 코드 실행에 대한 타임이 발생을 하기 때문에 60%정도로 딜레이를 줘야함

![image](https://user-images.githubusercontent.com/61939286/173382608-25888a1d-aa07-4828-86ec-4e83c52a6305.png)

![image](https://user-images.githubusercontent.com/61939286/173382629-ccaeffb5-8b75-47ee-a766-18ae1f909603.png)

![image](https://user-images.githubusercontent.com/61939286/173382663-cb44be52-bbab-46b8-bf83-99682b38571c.png)

![image](https://user-images.githubusercontent.com/61939286/173382691-51bbb0d9-718c-485c-a4c1-aafba54c2826.png)
0.5초 켜져있고 0.5초 꺼져있는게 깜빡깜빡

![image](https://user-images.githubusercontent.com/61939286/173382740-5bbb4952-a748-4775-bd5f-86b2bb99fdec.png)

![image](https://user-images.githubusercontent.com/61939286/173382766-90c307e8-a8ad-453a-8e80-a6ba95eb9667.png)

![image](https://user-images.githubusercontent.com/61939286/173382792-6b7dc221-4e49-414c-8664-be0b3b339dc5.png)


