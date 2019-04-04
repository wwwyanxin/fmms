<template>
    <span>
        <el-input
                placeholder="请输入关键字"
                v-model="inputValue"
                clearable
                @keyup.enter.native="searchValue"
                style="margin-left:50px;width:350px"
        >
            </el-input>

            <el-button @click="searchValue" type="primary" icon="el-icon-search">搜索</el-button>
    </span>
</template>

<script>
    export default {
        name: "SearchBar",
        data(){
            return{
                inputValue: ''
            }
        },
        methods:{
            searchValue() {
                this.$emit('searchHandler',this.inputValue)
               /* this.$bus.$emit('contentHandler',{
                    func:'search',
                    searchValue:this.inputValue
                })*/
            }
        }
    }
</script>

<style scoped>

</style>
