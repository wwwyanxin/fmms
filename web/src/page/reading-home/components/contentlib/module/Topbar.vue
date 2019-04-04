<template>
    <div>
        <div style="margin:auto 15px;position: relative">
            <span class="demonstration">选择日期</span>
            <el-date-picker
                    v-model="date"
                    align="right"
                    type="date"
                    placeholder="选择日期"
                    @change="updateData"
                    :picker-options="pickerOptions"
                    style="width:140px;"
            >
            </el-date-picker>


            <FilterSelect @change="scoreSelectChange" :options="filterSelectScore" :placeholder="'评分'"
                          style="width:80px;margin-left:20px"></FilterSelect>

            <FilterSelect @change="statusSelectChange" :options="filterSelectStatus" :placeholder="'状态'"
                          style="width:95px;"></FilterSelect>

            <el-input
                    placeholder="请输入关键字"
                    v-model="inputValue"
                    clearable
                    @keyup.enter.native="searchValue"
                    style="width:200px;"
            >
            </el-input>

            <el-button @click="searchValue" type="primary" icon="el-icon-search">搜索</el-button>

            <Pagination :info="pagination" @change="pageChange"></Pagination>
        </div>
    </div>
</template>

<script>
    import dayjs from 'dayjs'
    import Pagination from "../../../../../components-ui/pagination/Pagination";
    import FilterSelect from "../../../../../components-ui/filterSelect/FilterSelect";

    export default {
        name: "topbar",
        components: {FilterSelect, Pagination},
        props: {
            pagination: {}
        },
        data() {
            return {
                pickerOptions: {
                    disabledDate(time) {
                        return time.getTime() > Date.now();
                    },
                    shortcuts: [{
                        text: '今天',
                        onClick(picker) {
                            picker.$emit('pick', new Date());
                        }
                    }, {
                        text: '昨天',
                        onClick(picker) {
                            const date = new Date();
                            date.setTime(date.getTime() - 3600 * 1000 * 24);
                            picker.$emit('pick', date);
                        }
                    }, {
                        text: '一周前',
                        onClick(picker) {
                            const date = new Date();
                            date.setTime(date.getTime() - 3600 * 1000 * 24 * 7);
                            picker.$emit('pick', date);
                        }
                    }]
                },
                filterSelectStatus: [
                    {
                        value: '未审核',
                        label: '未审核'
                    }, {
                        value: '审核通过',
                        label: '审核通过'
                    }, {
                        value: '已选中',
                        label: '已选中'
                    }, {
                        value: '已下架',
                        label: '已下架'
                    },
                ],
                filterSelectScore: (()=>{
                    let arr = []
                    for(let i = 10 ; i >= 0 ; i--){
                        arr.push({
                            value: i,
                            label: i
                        })
                    }
                    return arr
                })(),
                filterSelect:{
                    scoreArr:[],
                    statusArr:[]
                },
                date: new Date(),
                inputValue: ''
            }
        },
        methods: {
            // 状态筛选
            statusSelectChange(statusArr) {
                this.filterSelect.statusArr = statusArr || []
                this.filterContent()
            },
            // 分数筛选
            scoreSelectChange(scoreArr) {
                this.filterSelect.scoreArr = scoreArr || []
                this.filterContent()
            },
            // 触发Contentlib筛选事件
            filterContent(){
                this.$bus.$emit('contentHandler', {
                    func: 'filterContent',
                    filterSelect: this.filterSelect
                })
                this.scrollTop()
            },
            // 设置日期
            setTime(time){
                this.date = new Date(time)
            },
            // 更改日期会触发重新拉取文章的事件
            updateData() {
                if (!this.date) {
                    return
                }
                let day = dayjs(this.date.getTime());
                this.$bus.$emit('contentHandler', {
                    func: 'selectDate',
                    date: this.dateFormat(this.date.getTime())
                })
            },
            //日期格式化
            dateFormat(time){
              return  dayjs(time).format('YYYYMMDD')
            },
            // 分页切换
            pageChange(index) {
                this.$emit('paginationChange', index)
                this.scrollTop()
            },
            // 触发搜索事件
            searchValue() {
                this.$bus.$emit('contentHandler', {
                    func: 'search',
                    searchValue: this.inputValue
                })
                this.scrollTop()
            },
            scrollTop() {
                // 滚动table到页首
                document.querySelector('.el-table__body-wrapper').scrollTop = 0
            }
        },
        mounted() {
            // 初始化拉取当日的文章
            this.updateData()
        }
    }
</script>

<style scoped>

</style>
