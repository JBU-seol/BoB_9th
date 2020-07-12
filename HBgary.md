# BoB 9th
#### 이강석멘토님 과제 [9팀]

[![N|Solid](https://www.kitribob.kr/static/front/images/about/bob-logo.png)](https://www.kitribob.kr/)

###### 주제 : Wikileak에 노출된 메일을 읽어보면서 실무자 입장 & HBgary 입장 정리

## HBGary vs Client

![bob_bi_basic](https://user-images.githubusercontent.com/46625602/87209264-39a0ed00-c34c-11ea-968f-ea43468bf03b.jpg)

**Team 9**

 <table border="1" width=”380" align="center">
    <tr>
	<th>0</th>
	<th>1</th>
	<th>2</th>
	<th>3</th>
<th>4</th>
    </tr>
    <tr>
	    <td>강현중_6069</td>
	    <td>권용희_4879</td> 
	    <td>김경범_6349</td>
	    <td>김민우_3779</td>
    <td>김예령_5709</td>
	</tr>
	<tr>
	    <td>김청준_1579</td>
	    <td>박승원_5819</td>
	    <td>백지원_8349</td>
	    <td>서호진_8759</td>
	    <td>신수민_0099</td>
	</tr>
	<tr>
	    <td>오재욱_3019</td>
	    <td>이도현_5799</td>
	    <td>이진헌_2409</td>
	    <td>유성환_4149</td>
 	    <td>이슬기_8619</td>
	</tr>
	<tr>
	    <td>임재연_9329</td>
	    <td>주형욱_6419</td>
	    <td>조서연_4319</td>
	    <td>조을한_3949</td>
 	    <td>최근영_2829</td>
	</tr>
 </table>

**Team Leader: 이도현_5799**



### 1. Emails

**배경**

 실무자는 Runtime Analysis 기능을 사용하기 위해 제품을 구입했다.

**HBGary**

악성코드를 탐지, 격리 및 분석할 수 있는 다양한 악성코드 분석 도구와 컴퓨터 포렌식과 관련한 분석 도구를 제공하는 회사다.

**문제** 

Active Reversing 기능 중 Analyze Binary 수행 후 Global 섹션에 접근할 수 없는 버그가 발생했다.

**실무자 문제 문의**

버그 발생 신고 메일을 HBGary에 보낸 후 증거로 버그가 발생하는 영상과 현재 사용 중인 버전의 사용 설명서를 보냈다. 하지만 한 달간 답장을 받지 못해, 다시 문의하였다. 

**HBGary의 답변**

Responder 디버거는 아래의 이유로 지원이 종료될 예정이라고 말했다.

- 우수한 무료 디버거가 존재하기 때문에 디버거 개발에 투자하는 것은 의미가 없다고 생각했다.
- 새로 개발 중인 “Flypaper”는 디버거보다 사용하기 편하고, 소프트웨어 실행과 관련된 런타임 정보들을 자동으로 수집한다.

Responder 디버거는 “Flypaper”라는 동적 분석 디버거로 대체될 것이므로 “Flypaper” 사용을 권유하고 피드백을 요청했다.

**실무자의 반응**

- 버그에 대한 답변 대신 새로운 대안 제시에 실망했다.
- 실무자는 HBGary가 버그 패치에 관심을 가지길 바랐다.
- Runtime Analysis가 동작하지 않는 정확한 이유와 Responder를 사용하는 다른 Client들도 같은 문제가 발생했는지 알려달라고 요구했다.

**HBGary 내부 반응**

- 버그 패치 대신 향후 출시될 “Flypaper” 선사용을 보상으로 제공하고, “Flypaper”에 대한 피드백을 받고자 했다.
- 실무자의 반응에 당황하며 버그 패치나 환불을 논의했다.
- 후에 제품 구매의사가 있다면 라이선스 갱신 할인을 고객에게 제공하고자 했다.  

---

### 2. 기술적으로 어떤 것이 문제인가?

다음은 동적 분석(Active Reversing)을 사용하기 위해 타겟 프로세스에 “Analyze Binary”를 수행하는 과정이다.

1. Responder와 “WintelNodeAgent” 간 세션을 연결한다.
2. 타겟 프로세스를 실행한다.
3. WintelNodeAgent에 attach할 타겟 프로세스를 선택한다.
4. WintelNodeAgent가 실행되고 있는 머신의 모든 프로세스와 DLL 목록을 가져온다. 

![](https://lh3.googleusercontent.com/GNDMsrpPytfdIIoiY1VYZmsC0b7ryIKKVXTwnGfbmlrsjrV5wFehu06NNOmL7dDw-ytuLZaIK9g90njJLmmMuq036J7CktxuySVPlaCqvMYwv-zRIYdNBBFYm4fr4DZnyDwv1bM_)

<center>[그림1] attached 프로세스 정보</center>
프로세스와 DLL 목록에서 원하는 바이너리를 선택하면 Responder가 설치된 머신으로 가져올 수 있다. 이는 메모리에서 직접 추출한 바이너리이기 때문에 Packer 등 보호 기법이 해제된 상태다.**[5]**

![](https://lh5.googleusercontent.com/_cO0ZorhKhand2sSZVMg4_IYgRIKlKoKrCm5cQPspWvL6zK-ejn0gX3_R0xAlNPUd1OA5HNCo3cyhOp0SJpn-1sWKPgqD_wyXB4ahx40wODhALM-_o400POGUYkCZXF_6rK9X8co)

<center>[그림2] 정상적으로 Global 섹션이 생긴 모습</center>
가이드에서 타겟 프로세스에 "Analyze Binary"를 수행하면 "Global"이라는 섹션이 활성화 되며  sample points를 추가할 수 있게 된다.**[1]**

![](https://lh5.googleusercontent.com/lXp4vkl0Gp9HUKKIfzbA99xTeQbP8u-RhUxiXc2npLAyjjCLP8ob_6Kt1zIrYyn-5LbAKpTIUeK5agQSNhvKlcLOsWMpD0gC1fo_pFjFe1190GSeFInfDuF2PDcbf0llDcKcPrqQ)

<center>[그림3] 실무자의 Responder에서는 Global 섹션이 없는 모습</center>
그러나 HBGary에서 실무자의 Responder에서는 이 섹션이 활성화되지 않아 동적 분석이 불가능하다.**[2]**

유출된 회사 내부자 간의 메일에 의하면 BlackHat에서 시연한 내용의 대부분은 연구 결과로써 일부 기능만 Responder에 구현이 되었다. 그러나, 아래 세 가지 기능은 제공하지 않았다.**[3]**
- live debugging
- class reconstruction
- phase-space analysis 

---

### 3.실무자가 원했던 기능은 어떤 것인가?

HBGary Responder는 윈도우 운영체제에서 활성 메모리 전체 내용을 추출하고, 분석하여 컴퓨터 조사에 필요한 운영체제와 프로세스 정보를 찾아낸다. 이때 수집한 내용은 커널과 사용자 모드에서의 오브젝트, 구조체, 바이너리, 그 외 유용한 아티팩트들이다.**[5]**

HBGary Responder의 커널 디버거, 가상 머신 메모리 분석, 메모리 덤프는 모두 좋은 기능이지만 실무자가 요구한 것은 아니었다. 실무자는 “Runtime Analysis” 기능을 원했다.**[4]**

Runtime Analysis 기능 중 하나인 Active Reversing은 타겟 프로세스의 행위(파일 열기, 읽기, 쓰기 등)를 IDA 같이 실행 순서에 따라 그래프 구조로 표현한다. 

또 다른 기능인 Tracing은 원하는 API 콜이나 현 브레이크 포인트 위치에서 몇 번째 함수 호출 때 브레이크 포인트를 거는 작업을 할 수 있다. 호출뿐만 아니라 모든 인스트럭션을 잡을 수 있고, 데이터를 볼 수 있다.**[6]**

---

### 4. HBGary의 문제점은 무엇인가?

1. 책임감 결여 
	- 실무자의 문의에 즉각 응답은 커녕 1달이 지나도 답장을 주지 않았다.
	- 시장에 우수하고 무료인 디버거가 있기 때문에 디버거 개발은 의미가 없다고 하였다.
	- 받은 문의에 대해 다른 담당자에게 전달만 하고 이후 진행사항을 체크하지 않았다.
	- 자사의 디버거 기능을 모르는 책임자가 실무자에게 답장을 보냈다.
	- 구현되지 않은 live debugging 기능을 허위 광고해 프로그램 구매를 유도했다.

2. 사후대책 미흡
	- 실무자에게 디버거를 더 이상 지원하지 않을 것이라 했다.
	- 버그를 패치하지 않았다.

3. 고객의 요구 파악 및 문제점 해결 실패
	 - 실무자가 원하는 답을 주지 못했다. 
	 - 실무자가 원하는 Runtime Analysis 기능이 Responder에 추가되지 않았다. 
	 - 릴리즈 하지 않은 “Flypaper” 설명 문서와 다운로드 링크를 보내며 피드백을 받고자 했다.
	

---

### 5. Reference

**[1]** HBGary Responder v1.2 User Guide, pp.62-64 <br/>
**[2]** from. 이강석, to. bob@hbgary, 이메일 내용, 2009-2-16 08:52, https://wikileaks.org/hbgary-emails/emailid/64323<br/>
**[3]** from. greg@hbgary.com, to. bob@hbgary.com, 이메일 내용, 2009-02-23 14:24
https://wikileaks.org/hbgary-emails/emailid/66749<br/>
**[4]** from. 이강석, to. bob@hbgary, 이메일 내용, 2009-2-22 12:33, https://wikileaks.org/hbgary-emails/emailid/64323<br/>
**[5]** HBGary Responder v1.2 User Guide, p.7<br/>
**[6]** HBGary Responder v1.2 User Guide, pp.62-72<br/>
