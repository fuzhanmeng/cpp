import socket
import struct
import time
import threading

# 核心封包工具：将纯文本打包为严格的大端序 TLV 二进制流
def pack_tlv(msg_type, payload_str):
    payload_bytes = payload_str.encode('utf-8')
    # '!II' 强制网络大端序，封装 Type 和 Length
    header = struct.pack('!II', msg_type, len(payload_bytes))
    return header + payload_bytes

# 工作线程：模拟一个极其恶劣的公网客户端
def client_worker(client_id):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        sock.connect(('127.0.0.1', 8888))
        print(f"[Client-{client_id}] 物理连接建立成功。")
        
        # ==========================================
        # 极限测试 1：绝对粘包 (发送端强行将多个帧合并)
        # ==========================================
        p1 = pack_tlv(101, f"Msg1 from C-{client_id}")
        p2 = pack_tlv(102, f"Msg2 from C-{client_id}")
        p3 = pack_tlv(103, f"Msg3 from C-{client_id}")
        
        # 物理合体：一次 sendall 发送出去
        sock.sendall(p1 + p2 + p3)
        print(f"[Client-{client_id}] 已发送 3 个高频粘包帧。")
        
        # ==========================================
        # 极限测试 2：恶意半包 (发送端主动切断完整帧)
        # ==========================================
        p4 = pack_tlv(104, f"Half-Packet from C-{client_id}")
        
        # 先发送前 5 个字节 (4 字节 Type + 1 字节 Length)，故意截断包头！
        sock.sendall(p4[:5])
        print(f"[Client-{client_id}] 已发送恶意半包 (被截断的头部)。系统挂起 0.5 秒...")
        
        time.sleep(0.5) # 强行制造网络延迟
        
        # 发送剩余的字节
        sock.sendall(p4[5:])
        print(f"[Client-{client_id}] 已补发剩余碎片数据。")

        # ==========================================
        # 接收服务器的回显验证 (总共应收到 4 个响应)
        # ==========================================
        for i in range(4):
            # 严格按照 TLV 协议接收响应
            header_data = b''
            while len(header_data) < 8:
                chunk = sock.recv(8 - len(header_data))
                if not chunk: break
                header_data += chunk
                
            if len(header_data) == 8:
                resp_type, resp_len = struct.unpack('!II', header_data)
                
                payload_data = b''
                while len(payload_data) < resp_len:
                    chunk = sock.recv(resp_len - len(payload_data))
                    if not chunk: break
                    payload_data += chunk
                    
                print(f"[Client-{client_id}] 成功收到回显 <- Type: {resp_type}, 载荷: {payload_data.decode('utf-8')}")

    except Exception as e:
        print(f"[Client-{client_id}] 发生异常: {e}")
    finally:
        sock.close()

def main():
    print("=== 启动混沌压测客户端 ===")
    
    threads = []
    # 瞬间并发启动 5 个客户端线程
    # 这将完美触发你 C++ 服务器中 4 个 Sub Reactor 的轮询分发机制！
    for i in range(5):
        t = threading.Thread(target=client_worker, args=(i,))
        threads.append(t)
        t.start()

    for t in threads:
        t.join()
        
    print("=== 压测结束 ===")

if __name__ == '__main__':
    main()