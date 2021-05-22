# Socket_WX_Helper



## 项目介绍
          编译环境为VS2019 只支持微信3.2.1.112版本。会在项目右侧的Release中附上3.2.1.112微信版本的安装包，编译好的dll可在Release目录中找到。

### 主要功能:
    0.
    接收消息:
    
    
![image](https://github.com/2826430176/Wx_Socket_Helper/blob/main/Static/recv_msg.png)


    1. 
    发送普通文本消息:
        {
        "type": 1,
        "wxid":"wxid",
        "msg":"消息内容"
        }
    例如:{"type":1,"wxid":"filehelper","msg":"消息内容"}
    效果演示:
        aaaaaaaaaaaaaaaaaaaa
    2.
    发送名片
        {
            "type": 2,
            "wxid":"wxid",
            "source":"源wxid",
            "NickName":"昵称"
        }
    例如:
        bbbbbbbbbbb
    
        bbbbbbbbbbb        bbbbbbbbbbb        bbbbbbbbbbb

                bbbbbbbbbbb        bbbbbbbbbbb        bbbbbbbbbbb

                        bbbbbbbbbbb