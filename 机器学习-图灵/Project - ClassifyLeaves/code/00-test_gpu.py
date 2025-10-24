import torch
import time
import numpy as np

def test_gpu():
    print("===== GPU 可用性测试 =====")
    # 检查CUDA是否可用
    print(f"CUDA 是否可用: {torch.cuda.is_available()}")
    
    if torch.cuda.is_available():
        # 显示GPU信息
        print(f"\n当前GPU数量: {torch.cuda.device_count()}")
        for i in range(torch.cuda.device_count()):
            print(f"\nGPU {i} 信息:")
            print(f"名称: {torch.cuda.get_device_name(i)}")
            print(f"显存总量: {torch.cuda.get_device_properties(i).total_memory / 1024**3:.2f} GB")
            print(f"显存已用: {torch.cuda.memory_allocated(i) / 1024**3:.2f} GB")
            print(f"显存剩余: {torch.cuda.memory_reserved(i) / 1024**3:.2f} GB")
        
        print("\n===== GPU 性能测试 =====")
        # 矩阵运算测试
        sizes = [(1000, 1000), (2000, 2000), (4000, 4000)]
        
        for size in sizes:
            print(f"\n矩阵大小: {size[0]} x {size[1]}")
            
            # 在CPU上进行测试
            a_cpu = torch.randn(size)
            b_cpu = torch.randn(size)
            
            start_time = time.time()
            c_cpu = torch.matmul(a_cpu, b_cpu)
            cpu_time = time.time() - start_time
            print(f"CPU 计算时间: {cpu_time:.4f} 秒")
            
            # 在GPU上进行测试
            a_gpu = a_cpu.cuda()
            b_gpu = b_cpu.cuda()
            
            # 预热GPU
            torch.matmul(a_gpu, b_gpu)
            torch.cuda.synchronize()
            
            start_time = time.time()
            c_gpu = torch.matmul(a_gpu, b_gpu)
            torch.cuda.synchronize()
            gpu_time = time.time() - start_time
            print(f"GPU 计算时间: {gpu_time:.4f} 秒")
            print(f"GPU 加速比: {cpu_time/gpu_time:.2f}x")
            
            # 清理显存
            del a_gpu, b_gpu, c_gpu
            torch.cuda.empty_cache()
        
        # 测试GPU内存分配
        print("\n===== GPU 显存分配测试 =====")
        try:
            # 逐步增加显存使用量
            memory_sizes = [512, 1024, 2048]  # MB
            for size in memory_sizes:
                print(f"\n尝试分配 {size} MB 显存")
                # 计算需要的张量大小
                n = int(size * 1024 * 1024 / 4)  # 每个float32占4字节
                x = torch.zeros(n, device='cuda')
                allocated = torch.cuda.memory_allocated() / 1024**2
                print(f"成功分配 {allocated:.2f} MB 显存")
                del x
                torch.cuda.empty_cache()
                
        except RuntimeError as e:
            print(f"显存分配失败: {e}")
    
    else:
        print("未检测到可用的GPU，请确认CUDA环境是否正确安装")

if __name__ == "__main__":
    test_gpu() 