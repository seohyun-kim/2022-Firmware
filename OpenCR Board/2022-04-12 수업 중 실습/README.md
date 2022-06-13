## 2022-04-12   

![image](https://user-images.githubusercontent.com/61939286/173379361-92dd1bbb-1c8e-4346-b41e-151f69a30a2c.png)  

![image](https://user-images.githubusercontent.com/61939286/173379395-5ea5dee7-58a8-4d7a-8c18-dbe182a9b057.png)

![image](https://user-images.githubusercontent.com/61939286/173379432-6b1e3c44-ba2c-4095-93e8-d12b3c121973.png)

![image](https://user-images.githubusercontent.com/61939286/173379471-7eb2858c-c336-4d38-8854-48baf12103b1.png)  

```c
unsigned char c = 0x00; // 초기화 된 상태

// 0번 비트만 1로 만드려고 함
c |= 0x01; 

// 이제 7번 비트만 1로 만드려고 함
// =>  0번 비트를 0으로 만들어야 하는가? 0번 비트는 1로 남겨두어야 하는가?

```   

![image](https://user-images.githubusercontent.com/61939286/173379632-34a4a7a5-302a-4da4-ac8f-ff50f25bb651.png)  

- BSRR만 달라짐
- 빨간색 코드는 완전히 같으므로 아래코드는 안쓰는게 맞음!!
    - 이전 코드에 따라서 변화가 생기는지는 확인해봐야함
    
![image](https://user-images.githubusercontent.com/61939286/173379781-54dc2650-c41b-4785-b788-59c848697e1a.png)
![image](https://user-images.githubusercontent.com/61939286/173379802-26623489-fadb-43bd-a581-308c01557fdf.png)

- 이 코드를 실행시키면 과연
    1. 켜질까? ❌
    2. 꺼질까? ⭕
    3. 켜졌다가 꺼질까? ⭕
 
![image](https://user-images.githubusercontent.com/61939286/173379863-064c40d2-7ce5-48a1-839c-1296d522fd61.png)  

- 깜빡깜빡 거리지 않고 희미하게 켜져있음
- 엄청나게 빠르게 깜빡이기 때문
- 전기적으로 깜빡이기 때문에 사람 눈으로 못봐요~

![image](https://user-images.githubusercontent.com/61939286/173379968-0c37fc99-8bd8-4e46-ba53-a931a309911f.png)
