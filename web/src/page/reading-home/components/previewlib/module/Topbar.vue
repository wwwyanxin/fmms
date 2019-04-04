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
        </div>
    </div>
</template>

<script>
    import dayjs from 'dayjs'
    import Pagination from "../../../../../components-ui/pagination/Pagination";
    import FilterSelect from "../../../../../components-ui/filterSelect/FilterSelect";

    export default {
        name: "topbar",
        data() {
            return {
                pickerOptions: {
                    disabledDate(time) {
                        return time.getTime() > new Date(new Date().setHours(0,0,0,0));
                    },
                    shortcuts: [{
                        text: '今天',
                        onClick(picker) {
                            picker.$emit('pick', new Date(new Date().setHours(0,0,0,0)));
                        }
                    }, {
                        text: '昨天',
                        onClick(picker) {
                            const date = new Date(new Date().setHours(0,0,0,0));
                            date.setTime(date.getTime() - 3600 * 1000 * 24);
                            picker.$emit('pick', date);
                        }
                    }, {
                        text: '一周前',
                        onClick(picker) {
                            const date = new Date(new Date().setHours(0,0,0,0));
                            date.setTime(date.getTime() - 3600 * 1000 * 24 * 7);
                            picker.$emit('pick', date);
                        }
                    }]
                },
                date: {},
            }
        },
        methods: {
            // 更改日期会触发重新拉取文章的事件
            updateData() {
                if (!this.date) {
                    return
                }
                this.$emit('changeDate', this.date)
            },
        },
        mounted() {
            // 获得当天0点的时间戳
            let date = new Date(new Date().setHours(0,0,0,0))
            this.date = date
            // 初始化拉取当日的文章
            this.updateData()
        }
    }
</script>

<style scoped>

</style>
