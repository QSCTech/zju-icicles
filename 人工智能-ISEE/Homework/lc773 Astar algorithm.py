class AStar:
    # 计算启发函数  所有元素到目标位置的距离和
    # 1 0 0 , 2 [01] 3 [02] 4 [10] 5[11] 0 [12]
    @staticmethod
    def getH(status: str, target: str) -> int:
        ret = 0
        for i in range(6):
            dist = abs(int(status[i]) - int(target[i]))
            ret += min(dist, 10 - dist)
        return ret

    def __init__(self, status: List[List[int]], target: List[List[int]], g: str) -> None:
        self.status = status
        self.g = g
        self.h = AStar.getH(status, target)
        self.f = self.g + self.h
    
    def __lt__(self, other: "AStar") -> bool:
        return self.f < other.f

class Solution:
    def slidingPuzzle(self, board: List[List[int]]) -> int:
        if target == "0000":
            return 0

        dead = set(deadends)
        if "0000" in dead:
            return -1
        
        def num_prev(x: str) -> str:
            return "9" if x == "0" else str(int(x) - 1)
        
        def num_succ(x: str) -> str:
            return "0" if x == "9" else str(int(x) + 1)
        
        def get(status: str) -> Generator[str, None, None]:
            s = list(status)
            for i in range(4):
                num = s[i]
                s[i] = num_prev(num)
                yield "".join(s)
                s[i] = num_succ(num)
                yield "".join(s)
                s[i] = num

        q = [AStar("0000", target, 0)]
        seen = {"0000"}
        while q:
            node = heapq.heappop(q)
            for next_status in get(node.status):
                if next_status not in seen and next_status not in dead:
                    if next_status == target:
                        return node.g + 1
                    heapq.heappush(q, AStar(next_status, target, node.g + 1))
                    seen.add(next_status)
        
        return -1