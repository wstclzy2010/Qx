1、更新数据库中数据，首先要read，再改值，最后再更新；

总结：
1、代码移植

2、数据库字段的属性设置
设置主键 pk    当模型没有设置主键时，符合上述类型且名称为Id的Field将被视为自增键（主键）；
自增 auto
全局唯一 unique
设置允许为空 null
设置长度 size()
设置默认值 default()
浮点数精度 digits(12);decimal(4)   12345678.1234
时间的设置 date datetime time.time    type(date)/type(datetime)
          auto_now  
          auto_now_add

3、getstring()获取传过来的数据

4、静态文件的上传，注意：1）前端内容，form一定要设置enctype="multipart/form-data"
                       2）注意对上传文件的处理  f,h,err := getfile() //f为文件流，要及时关闭，defer f.close()；h,文件头；
                       3）savetofile()文件的存储：文件的判断、判断类型、判断大小，防止文件名重复——把文件名命名为时间，降低了重复的可能；

5、视图语法  循环   range 将数组、切片

6、URL传值  /update?id={{.Id}}  1)在路由里面不会匹配?后面的内容
                                2）获取url传值的方法:getint()或者getstring()

7、删除功能的实现       js代码（删除前询问是否确认！！！） 软件友好度