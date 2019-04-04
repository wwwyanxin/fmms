## 关于项目
* cgi调试页: http://113.96.202.104/oa/test
* 已接入智能网关(统一登录)
* 开发页: http://xmail.oa.com/templates/read-home.html
* 上线部署: http://xmail.oa.com/oa/call?func=4&t=read-home
## 目录结构
* reading项目下包括文章管理、卡片管理、标签管理、媒体管理四个模块。
分别对应contentlib、clusterlib、taglib、medialib。
* 每个模块下有一个名为***lib.vue的主组件,用来操作数据,以及请求接口。
* 模块对应的module为模块所需的子组件,用来展示table数据,编辑等操作
* 注意taglib下有tag1和tag2两个组件,分别对应一级标签和二级标签的主组件,
这样的设计是考虑到今后会添加三级,四级标签,而之后标签的设计是不确定的,
所以每一级标签单独做一份,但是有部分重复代码,有精力可以重构一下.
* 每个模块数据是不互通的,各自维护一份数据. 
* config下是黑名单配置,由于后台暂时未提供黑白名单功能,
所以前端来维护这个名单,等后台支持后,可以直接拉后台数据,并且完善媒体管理模块.

## contentlib文章管理
* 每个功能模块的设计结构类似,卡片管理和标签管理以此类推。
* 拉取某天的文章信息,拥有黑名单过滤、搜索关键字、分页、状态过滤的功能。
```
allArticles: [],  // 黑名单过滤后的文章
tmpArticles: [],  //用于筛选过滤
currentArticles: [], // 用于分页
```
拉取文章的动作由Topbar中的时间选择器触发
```vue
updateData() {
    if (!this.date) {
        return
    }
    let day = dayjs(this.date.getTime());
    this.$bus.$emit('contentHandler', {
        func: 'selectDate',
        date: day.format('YYYYMMDD')
    })
},
```
Contentlib监听此事件
```vue
case 'selectDate': {
    this.tableLoading = true
    this.bookdate = param.date
    try {
        await this.updateArticles({func: 1, bookdate: param.date})
        this.tablePagination.total = this.allArticles && this.allArticles.length
        this.fetchData(1, this.tablePagination.pageSize)
        this.$message({
            type: 'success',
            message: '文章已更新!'
        });
    } catch (e) {
        this.$message({
            type: 'error',
            message: '文章更新失败!'
        });
        console.log(e)
    }
    break
}
```
首先拉取某个日子的全部文章信息,进行黑名单过滤,结果放到allArticles,
此时tmpArticles等于allArticles  
在进行分页,将当前页的文章放入currentArticles中,  
如果进行关键词筛选或者状态过滤(已审核、未审核等),
将allArticles中的文章按条件进行过滤后,保存在tmpArticles中,
再将过滤后的tmpArticles进行分页保存在currentArticles中
* 文章打分、打标签等操作,由table组件触发给contentlib, 并且携带此文章的信息,
contentlib收到信息后,将相应的操作框(xxxBox)显示出来,并将信息通过props传递进去.
当操作修改完成,点击确认时,会触发给contentlib的contentHandler方法,由contentlib去调用接口
```vue
created() {
    this.pullTagList()
    this.pullTopics()
    this.$bus.$on('contentHandler', this.contentHandler)
},
beforeDestroy() {
    this.$bus.$off('contentHandler', this.contentHandler)
},
methods: {
    async contentHandler(param) {
        switch (param.func) {
            case 'optScore': {
                this.articleInfo = {
                    ...param.args,
                }
                this.$refs.scoreBox.show()
                break;
            }
            case 'optContentTag': {
                this.articleInfo = {
                    ...param.args,
                }
                this.contentTagInfo.selected.tagSelect1 = param.args.tagSelect1
                this.contentTagInfo.selected.tagSelect2 = param.args.tagSelect2
                this.$refs.contentTagBox.show()
                break
            }
            // ...省略
    },
}
```
## clusterlib卡片管理
* 有部分特殊卡片,屏蔽掉编辑按钮,由后台去管理

## taglib标签管理
* tag1是一级标签,可关联二级标签
* 一级标签中有个banner特殊的标签,特殊处理

