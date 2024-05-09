# 計算機功能
支援Integer(整數)、Decimal(小數)運算與變數功能，亦即可以定義變數及變數的型態

## 運算子優先權
| 優先權 | 運算子 | 相同層級的運算順序|
| ----- | ----- | ------------- |
| 1     | ()    |               |
| 2     | !     | 由左至右|
| 3|^|由右至左|
|4|+- (正負號)|由右至左
|5|* /|由左至右
|6|+ -|由左至右
## 說明
* 整數與整數運算其結果為整數。
* 整數與浮點數運算其結果為浮點數(順序相反亦然)。
* 除了支援任意數之間的加減乘除之外，還要有 Power(冪次)及正整數的 Factorial(階乘)。
* 輸出 Decimal 時，請直接輸出至小數點後 100 位，不必四捨五入或者無條件進位等動作，Decimal 的小數請以分數實作。<br/>亦即：1.0 / 3.0 * 3 = 1.00000000…，而非 0.999999999999...。
* 程式必須可以讓使用者將任意運算式的值賦予變數，而且可以重新賦值，例如：
Set Integer A = 100 + 5! + Power(5, 2)
Set Integer A = 3
Set Decimal A = 1.0
A = A + A
* 輸出時機
```
Set Integer A = 3 // 不用輸出
A = 1 + 5 // 不用輸出
A // 輸出 6
A + A // 輸出 12
1 * 33 + 4 // 輸出 37
```
* 當輸入非法運算式 (Ex: 除 0、小數的階乘)，需要輸出錯誤資訊
* 輸入以空白字元做切割(Ex: 1 + 2 * 3)

## 基本功能
* 任意四則運算式(加減乘除以及括弧運算)，且滿足先乘除後加減，由左至右的求值順序。
  * Ex：1.5 + 3 * ( -(-5) )
* 將精確度較高的型別指派給精確度較低型別之變數，自動捨去高精度資訊
  * Ex：Set Integer A=3.5 
  * //這樣 A 會是 3
* 運算式的階乘運算 a!，其中 a 必為任意整數的運算結果(也必為正整數)
  * Ex：(2+4)!
  * Ex：1 + ( 3 * 5 ) !

## 小數功能
* 以分數格式儲存
  * Ex：1/3.0 * 3 答案為 1
* 運算輸出時精確度為 100 位
  * Ex：輸出 1/3.0 = 0.33333 … 3
  * // 有 100 個 3
* 可將小數運算結果套用到階乘，需要判斷小數運算的結果是否為整數
  * Ex：(1/3.0 * 6)!

## API設計
* 為 Decimal、Integer 重載operator <<, >>, +, -, *,/，使這兩種型別可以進行複合運算，並且可以使用std::cout 以及 std::cin 進行輸出輸入
  * Integer i;
  * Decimal d;
  * cin >> i >> d;
  * cout << i + d;
* 為 Decimal、Integer 重載Constructor，可以直接賦予字串進行初始化
  * Integer i = "12345"; 
  * Decimal d = "0.3 * 3";
* 繼承共同基底類別或者使用其 它設計技巧，使得兩種型別可以放入同一容器中，並且可以 走訪所有儲存的元素然後加以輸出。
  * Integer i = "123";
  * Decimal d = "123.3"; 
  * vector<NumberObject*> nums; 
  * nums.push_back(&i); 
  * nums.push_back(&d); 
  * for(const auto& num : nums) 
  * cout << *num << endl;

# class之間的關係
## 數字計算
* NormalArithmetic: 定義大數計算的functions
* MathExpression: 繼承NormalArithmetic，將數字轉為分數，即分子與分母。operator overloading將 +, -, *, / 等運算重新定義，並利用NormalArithmetic的function進行大數運算。

## API設計
* Basic: 讓Integer與Decimal繼承之用，利用virtual function與operator overloading實現多型
* Integer: 繼承Basic。overwrite virtual function與定義operator overloading達到多型
* Decimal: 繼承Basic。overwrite virtual function與定義operator overloading達到多型

## 解析輸入
* Parser: 解析四則運算
* Token: 紀錄輸入的變數
