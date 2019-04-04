<template>
    <el-select @change="selectChange" v-model="selectValue" multiple :placeholder="placeholder">
        <el-option
                v-for="item in options"
                :key="item.value"
                :label="item.label"
                :value="item.value"
        >
        </el-option>
    </el-select>

</template>

<script>
    export default {
        name: "FilterSelect",
        props: {
            options: {
                type:Array
            },
            placeholder:{
                type: String,
                default: '请选择'
            }
        },
        data() {
            return {
                selectValue: [],
            }
        },
        methods:{
            selectChange(selectArr){
                this.$emit('change',selectArr)
            }
        }
    }
</script>

<style scoped>

</style>
