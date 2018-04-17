# NQueens-Problem-with-heuristic-algorithm

In the classic N-Queens Problem, we use backtracking method to calculate all the solutions. In this file on another hand, we try to use a heuristic algortihm to "speculate" or "guess" in an effor to derive one of the solution to N-Queens Problem.

And in "nqueens.cpp", we set the number N at the beginning, and the programme will exit after deriving 100 global optimal solutions, aka the solution to N-Queens(whereas a locally optimal solution is not a real solution to our problem).

"queen_seq" in the C++ file is a vector of length N, representing the position of each queen(each row has only one queen).
"hf" is the evaluation function, the queen who has the largest hf will be moved. The actual meaning of hf is the 'conflict number' of each queen.

在nqueens.cpp中在宏中设置N皇后的N值，程序找到100个全局最优解（即N皇后的解）后会退出，
并输出文件output.txt记录每一次得解所用步数（即找到几个不合格的局部最优解）以及所用时间，单位为s。同时也会输出平均用时。

在附件中90queens.txt为一个测试记录，平均用时分别为53s。

代码的一些说明：
	queen_seq：长度为N的vector，代表每行存的皇后的位置
	hf：长度为N的vector，代表每行的皇后的评价函数，实际是它的“冲突数”

	实现：
	每一步是找到目前hf最大的一个皇后，然后判断出能使它hf最小的位置，并移动它到这个位置
	不断重复这一步直到满足退出条件，即原位置与新位置相同
	退出后判断这是局部最优解还是全局最优解
	若为全局最优解，记录一次成功记录，开始下一次“爬山”（目前设定是共要成功100次，最后求出平均成功用时）
	若为局部最优解，随机重启后再次开始“爬山”

	可改进之处：
	“爬山”过程可以不用直接移到hf最小处，可以采用模拟退火算法，这样可以减少每次找全局解需要的重启（或尝试）次数，但每次会走更多步
	究竟哪种方法更快很难说

