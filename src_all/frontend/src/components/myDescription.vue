<!-- myDescription.vue -->
<template>
  <div class="description">
    <h1>北京故宫</h1>
    <h2>the Forbidden City</h2>
    <!-- 这里的描述内容是固定的，不需要从外部传入 -->
    <p>故宫又称紫禁城。中国古代讲究“天人合一”的规划理念，用天上的星辰与都城规划相对应，以突出政权的合法性和皇权的至高性。天帝居住在紫微宫，而人间皇帝自诩为受命于天的“天子”，其居所应象征紫微宫以与天帝对应，《后汉书》载“天有紫微宫，是上帝之所居也。王者立宫，象而为之”。紫微、紫垣、紫宫等便成了帝王宫殿的代称。由于封建皇宫在古代属于禁地，常人不能进入，故称为“紫禁”。明朝初期同外禁垣一起统称“皇城”，大约明朝中晚期，与外禁垣区分开来，即宫城叫“紫禁城”，外禁垣为“皇城”。</p>
    <!-- 可以添加更多固定内容 -->
    <!-- 跳转到路线规划页面的按钮 -->
    <button @click="goToRoutePlanner">开始路线规划</button>
  </div>
</template>

<script>
import { useRouter } from 'vue-router';

export default {
    name: 'myDescription',

    setup() {
    const router = useRouter(); // 创建 router 实例

    // 定义跳转到路线规划页面的函数
    const goToRoutePlanner = () => {
      router.push('/route-planning');
    };

    return {
      goToRoutePlanner, // 将函数暴露给模板
    };
  },
};
</script>

<style scoped>
/* 你的 CSS 样式 */
</style>