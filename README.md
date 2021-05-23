# Socket_WX_Helper

## 要求

+ [jsonxx](https://www.runoob.com)


## 项目介绍
          编译环境为VS2019 只支持微信3.2.1.112版本。会在项目右侧的Release中附上3.2.1.112微信版本的安装包，编译好的dll可在Release目录中找到。

### 主要功能:
  0.
    接收消息:
    
    
![image](https://github.com/2826430176/Wx_Socket_Helper/blob/main/Static/recv_msg.png)


  + 1. 发送普通文本消息:
    ```
      {
        "type": 1,
        "wxid":"wxid",
        "msg":"消息内容"
      }
             例如:{"type":1,"wxid":"filehelper","msg":"消息内容"}
     ```        
    效果演示:
![image](https://github.com/2826430176/Wx_Socket_Helper/blob/main/Static/%E5%8F%91%E9%80%81%E6%99%AE%E9%80%9A%E6%B6%88%E6%81%AF.png)


   + 2. 发送名片
```javascript
    {
            "type": 2,
            "wxid":"wxid",
            "source":"源wxid",
            "NickName":"昵称"
    }

例如:{"type": 2,"wxid":"filehelper""source":"wxid_4zr616ir6fi122""NickName":"昵称"}
```

效果演示:

![image](https://github.com/2826430176/Wx_Socket_Helper/blob/main/Static/sendxmlcard.png)


  + 3. 通过wxid获取好友详细信息
```javascript
  {
    "type": 3,
    "wxid":"wxid",
  }
```
例如:

        {"type": 3,"wxid":"wxid_4zr616ir6fi122",}

效果演示:
![image](https://github.com/2826430176/Wx_Socket_Helper/blob/main/Static/wxid%E8%8E%B7%E5%8F%96%E8%AF%A6%E7%BB%86%E4%BF%A1%E6%81%AF.jpg)


  + 4. 遍历二叉树获取好友列表
```javascript
{
    "type": 4,
}
```
例如:

        {"type": 4}

效果演示:

![image](https://github.com/2826430176/Wx_Socket_Helper/blob/main/Static/%E8%8E%B7%E5%8F%96%E5%A5%BD%E5%8F%8B%E5%88%97%E8%A1%A8.png)

 + 5.  通过wxid获取好友详细信息
```javascript
  {
    "type": 3,
    "wxid":"wxid",
  }
```
例如:

        {"type": 3,"wxid":"wxid_4zr616ir6fi122",}

效果演示:

    ![image](https://github.com/2826430176/Wx_Socket_Helper/blob/main/Static/wxid获取详细信息.jpg)


