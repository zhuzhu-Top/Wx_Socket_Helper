# Socket_WX_Helper

## 要求

+ [jsonxx](https://github.com/Nomango/jsonxx)
           
## 2021/7/3更新
   支持最新微信(3.3.0.104)  
   在release中下载最新的dll和服务端(还有使用接口)(先启动服务端，再注入微信) 
           
## 项目介绍
  编译环境为VS2019 只支持微信3.2.1.112版本。会在项目右侧的Release中附上3.2.1.112微信版本的安装包，编译好的dll可在Release到，该项目使用socket通信，只要是支持socket的语言都可以使用。(如果你不会写的话，可以加群找我要)

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


#### python控制台收到的并不是错误的，这个是编码后的，可以用utf8解开还原成中文，我实力太菜，就不想折腾了

 + 5.  通过wxid获取好友详细信息
```javascript

  {
    "type": 3,
    "wxid":"wxid",
  }

```
例如:

      {"type":3,"wxid":"wxid_4zr616ir6fi122"}

效果演示:

![image](https://github.com/2826430176/Wx_Socket_Helper/blob/main/Static/wxid%E8%8E%B7%E5%8F%96%E8%AF%A6%E7%BB%86%E4%BF%A1%E6%81%AF.jpg)

---

 + 5.  通过wxid关注公众号

```javascript
  {
    "type": 12,
    "wxid":"wxid",
  }

```

效果演示:
![image](https://github.com/zhuzhu-Top/Wx_Socket_Helper/blob/main/Static/add_public.png)

----
#### 这里还有一些别的个人信息，我只是没有取出来，有需要的话，可以自己看下我的代码去取出来，我写的都挺简单易懂的(太懒了,没办法-_-)


### 余下的功能就不一一演示了，第一次开源项目，github都不太会用，后面闲着没事了，如果有需要的话我会完善的，我的所用功能都在socketMain里可以找到。




----

### 我写这个项目的目的，只是单纯的想考验下我自己的实力，FindPattern库是我偶然一次看到大佬发出来的，这个特征码匹配的还是很不错的，我本来想的是全部功能都用特征码实现，后面发现太麻烦了，就放弃了，ZZHook是我自己封装的，我个人感觉还是挺方便的，我在hook 消息的时候有用到，有兴趣的一看看



###声明
本项目仅供技术研究，请勿用于任何商业用途，请勿用于非法用途，如有任何人凭此做何非法事情，均于作者无关，特此声明。
