<template>
    <div>
        <el-autocomplete style="display: block;" :style="{width:`${info.width ? info.width : 300}px`}"
                         v-model="searchValue"
                         :fetch-suggestions="searchHandler"
                         :placeholder="info.placeholder"
                         @select="selectHandler"
                         clearable
        ></el-autocomplete>
        <el-tag style="margin-right:10px"
                v-for="(item,index) in selected"
                :key="index"
                closable
                @close="closeTag(index)"
                :type="info.tagType">
            {{item.name}}
        </el-tag>
    </div>
</template>

<script>
    export default {
        name: "SearchAppend",
        props:{
            info:{
                selected:[],
                allDatas: [],
                placeholder:'',
                tagType:'',
                width:{
                    type: Number,
                    default: 300
                }
            },
        },
        data(){
            return{
                searchValue:'',
                selected:this.info.selected ||[]
            }
        },
        watch:{
          'info.selected': function () {
              this.selected = this.info.selected || []
          }
        },
        methods:{
            selectHandler(item) {
                if (this.selectCheck(this.selected,item.value)) {
                    this.selected.push({
                        name: item.value,
                        id:item.id
                    })
                    //清空输入框
                    this.searchValue = ''
                }
            },
            selectCheck(arr,value) {
                let res = arr.filter(this.equalFilter(value, 'name'))
                if (!res || res.length === 0) {
                    return true
                } else {
                    this.$message({
                        message: `重复添加${value}`,
                        type: 'warning'
                    });
                    return false
                }
            },
            equalFilter(queryString, field) {
                return (state) => {
                    return (state[field] === queryString);
                };
            },
            searchFilter(queryString, field) {
                return (state) => {
                    return (state[field].toLowerCase().indexOf(queryString.toLowerCase()) !== -1);
                };
            },
            searchHandler(queryString, cb) {
                var results = queryString ? this.info.allDatas.filter(this.searchFilter(queryString, 'value')) : this.info.allDatas;
                cb(results || []);
            },
            closeTag(index) {
                this.selected.splice(index, 1)
            },
        },
    }
</script>

<style scoped>

</style>
