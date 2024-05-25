<template>
    <div class="write-diary">
        <button @click="goBack">返回</button>
        <h1>写日记</h1>
        <!-- 表单输入 -->
        <form @submit.prevent="submitDiary">
            <div>
                <label for="title">标题:</label>
                <input type="text" id="title" v-model="diary.title" required>
            </div>
            <div>
                <label for="author">作者:</label>
                <input type="text" id="author" v-model="diary.author" required>
            </div>
            <div>
                <label for="description">描述对象/地点:</label>
                <input type="text" id="description" v-model="diary.description" required>
            </div>
            <div>
                <label for="content">日记内容:</label>
                <textarea id="content" v-model="diary.content" required></textarea>
            </div>
            <!-- 提交按钮 -->
            <button type="submit">上传</button>
        </form>
    </div>
</template>

<script>
import { ref } from 'vue';
import axios from 'axios';
import { useRouter } from 'vue-router';

export default {
    name: 'WriteDiary',

    setup() {
        const router = useRouter();
       const diary = ref({
      title: '',
      author: '',
      description: '',
      content: '',
    }); // 存储日记表单数据 

        const submitDiary = async () => {
            try {
                const response = await axios.post('/api/diary-write', diary.value);

                if (response.data.success) {
                    alert('日记上传成功'); // 告知用户上传成功
                    // 可能还需要在这里做其他事情，比如重定向或清空表单
                } else {
                    console.error('上传失败:', response.data.message);
                }
            } catch (err) {
                console.error('上传日记时发生错误:', err);
                alert('上传日记时发生错误，请稍后重试'); // 告知用户错误
            }
        };

        // 返回按钮
        const goBack = () => {
            router.go(-1); // 返回上一页
        };

        return {
            diary,
            submitDiary,
            goBack,
        };
    },
};
</script>

<style scoped>
/* 表单样式 */
.write-diary {
  max-width: 600px;
  margin: 0 auto;
  padding: 20px;
  border: 1px solid #ddd;
  border-radius: 4px;
}

form > div {
  margin-bottom: 15px;
}

label {
  display: block;
  margin-bottom: 5px;
}

input[type="text"],
textarea {
  width: 100%;
  padding: 8px;
  border: 1px solid #ddd;
  border-radius: 4px;
}

button {
  padding: 10px 20px;
  background-color: #42b983;
  color: white;
  border: none;
  border-radius: 4px;
  cursor: pointer;
}

button:hover {
  background-color: #369f7e;
}

/* 其他样式 */
</style>