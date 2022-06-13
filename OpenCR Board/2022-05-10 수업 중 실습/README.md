# 2022-05-10 수업 중 실습 (외부 회로 사용)

![image](https://user-images.githubusercontent.com/61939286/173383136-b55460a6-63a4-4305-8cf8-eaa0c2e7f1d2.png)
![image](https://user-images.githubusercontent.com/61939286/173383170-4f680c96-78f6-4208-acfe-8d315ea9bd2b.png)

- 외부 회로를 구현 할 때에는 순서가 중요함!!!!!

<aside>
💡 순서 주의!!

1. 1. USB 뺸다
2. 브레드 보드에서 회로 꾸민다!
3. 이클립스에서 코딩하고 빌드 까지 함(에러 없는 상태)
4. 브레드 보드의 전선을 메인보드와 연결 (- 부터)
5. 이제야 보드와 pc usb연결
6. 보드를 가능한 만지지 않음(정전기 주의)
7. 디버깅 / 실행
</aside>

- **LED 다리 긴 쪽이 +**
- 모든 LED **앞**에는 저항 하나를 붙이자.... **전원들어오는 쪽!!!!!**

![image](https://user-images.githubusercontent.com/61939286/173383332-1d6a2be4-fa8c-445a-8dbf-74d43d7823d8.png)

- GPIO 에서 3.3V를 내 보낼거임
- BSSR이 0이라고 주기 전에 OUTPUT모드 설정하는 순간 LED 켜질 수 있음

![image](https://user-images.githubusercontent.com/61939286/173383413-cac2684a-2a58-4555-9bc8-8c0888d17f05.png)


> **클락 번호를 주의하자!!!! 내가 0번 비트부터 만들어놨으면서!!!!!!!!!!**

<br/>  


![image](https://user-images.githubusercontent.com/61939286/167565367-009911b1-d5b4-45af-8e33-e56f46797e19.png)

![image](https://user-images.githubusercontent.com/61939286/167565441-86dcef4b-6b14-4f3d-97e9-0831295da27a.png)

![image](https://user-images.githubusercontent.com/61939286/167565481-f45b1cda-b8a7-4db0-ae93-f8ce3d78297f.png)


