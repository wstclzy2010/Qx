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




---------------------------------------------------------------------------------------------
beego支持用户定义视图函数：{{.content|FuncName}} // .content为后台传输的数据，作为视图函数的参数；
相应的在后台要有函数的定义：func hello(in string) (out string){
    out=in+"world"
    return
}
然后在main函数中给这两个名字做映射，就能调用:beego.AddFuncMap("FuncName",hello)

视图的if-else比较语法：
{{if compare .FirstPage true}}
    <li> 上一页 </li>
{{else}}
    <li><a href="/">上一页</li>
{{end}}

--主外键关系
constraint FK_主表_从表 foreign(外键字段) references 主表(主表主键字段)

文章类型和文章表为一对多关系
创建表映射关系：文章表中增加类型字段 并设置 'orm:"rel(fk)"' //设置外键 //此字段会出现在文章表中！
               类型表中增加文章字段，并设置 'orm:"reverse(many)"' //注意此字段不会在该表中出现！
                reverse和rel必须成对出现；

一对多：加外键
多对多：额外会加一张关系表！ //rel(m2m)

分页功能实现：
1、确定出每页显示多少条记录；
2、计算出总的记录count，err := o.QueryTable("Article").Count()
3、根据1和2，可以求出总页数：结合float型 做除法，并借助天花板函数ceil()，向上取整；
    _,err :=o.QueryTable("Article").qs.All(&articles) //拿到所有记录，存入articles切片；
    limit(pagesize,start)//第一个参数为页面大小，第二个参数为起始位置（对应记录index）；
4、实现首页末页功能：首先把当前页码传递给视图this.Data，然后对数据处理(上一页，页码-1，下一页，页码+1)；
5、实现上一页，下一页功能：首页 末页的上一页 下一页细节处理————用视图函数和视图判断语法。



获取添加型业务：
1、获取数据；
2、判断数据；
3、执行插入操作；
4、展示视图：1）this.Tplname; 2)this.Redirect("/....",302)；


多表查询：
注意orm使用的是惰性查询，如何避免：RelatedSel("ArticleType") //关联起来，如果没有这句，即使Filter了也不会去查ArticleType表！！！！
o.QueryTable("Articles").RelatedSel("ArticleType").Filter("ArticleType__TypeName", typeName).All(&articles)