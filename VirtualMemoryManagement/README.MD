
# 가상 메모리 관리 기법의 하나인 페이지 교체 기법 중 OPT / FIFO / LRU / Second_Chance를 구현하고 과정을 보여주는 시뮬레이터 구현


차   례


1장. 	프로젝트 동기/목적 
 	
2장.		설계/구현 

3장	.	수행결과(구현 화면 포함)

4장	.	결론 및 보충할 것

----------------------------------------------------------

결과를 비교해보았을 때 OPT 기법이 압도적으로 page fault가 적다. 하지만 언급했던 거처럼 현실적으로 이후 들어올 page를 예측하는 것은 불가능에 가깝다. 
 
다른 3개기법을 비교해 보자.

 FIFO의 경우 평균적으로 비슷한 page fault 횟수를 나타내고 패턴의 영향을 제일 덜 받았다.
LRU의 경우 반복적으로 주어지는 page reference string에서 강점이 나타났다. ( input2.txt 참고 )
Second_chance 의 경우 page fault에 있어서 특이점을 찾지 못했다. 

 현재 제일 많이 사용하는 페이지 관리기법은 LRU라고 한다. 실생활에서 우리는 자주 사용하는 프로그램이 있고 자주 사용하지 않는 프로그램이 명확히 나누어져 있다. 그래서 같은 page 가 반복적으로 나타나는 현실의 경우에서는 LRU 관리 기법이 제일 효과적일 것이라고 예측한다. 

 page reference string의 패턴에 따라 효과적인 기법이 각각 다르다고 볼 수 있다. 하지만 역시 현실에서는 단순히 page fault 가 적다고 효율적인 관리기법이라고 하기는 어렵다. overhead도 생각해야하며 다른 영향을 미치는 factor 도 존재할 것이다. 하여 제일 효율적/ 좋은 관리기법은 콕 집어 말할 수 없을 것 같다. 

개인 적인 생각을 추가하자면 opt 관리 기법이 완벽히 불가능하다고 생각하지는 않다. 사용자의 CPU 이용 패턴에는 특정 패턴들이 존재할 것이고 이를 저장해 놓거나 빅데이터의 개념으로 접근 한다면 특정 상황에서는 OPT 관리기법을 사용할 수 있는 시간이 존재할 것이라고 생각한다.
