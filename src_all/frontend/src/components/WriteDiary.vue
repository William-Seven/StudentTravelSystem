<template>
    <div class="background"></div>
    <form class="form">
        <div class="write-diary">
            <button class="return_button" @click.prevent="goBack">返回</button>
            <h1 class="title">写日记</h1>
            <!-- 表单输入 -->
            <form @submit.prevent="submitDiary">
                <div>
                    <label class="label_title" for="title">标题:</label>
                    <input type="text" id="title" v-model="diary.title" required>
                </div>
                <div>
                    <label class="label_author" for="author">作者:</label>
                    <input type="text" id="author" v-model="diary.author" required>
                </div>
                <div>
                    <label class="label_description" for="description">描述对象/地点:</label>
                    <input type="text" id="description" v-model="diary.description" required>
                </div>
                <div>
                    <label class="label_content" for="content">日记内容:</label>
                    <textarea id="content" v-model="diary.content" required></textarea>
                </div>
                <!-- 提交按钮 -->
                <button class="submit_button" type="submit">上传</button>
            </form>
        </div>
    </form>
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
.background {
  position: absolute;
  width: 100%;
  height: 100%;
  margin: 0;
  padding: 0;
  background-attachment: fixed;
  overflow: hidden;
  background-image: url('~@/assets/img/background.png');
  background-size: cover;
}

.background::before {
  content: "";
  position: fixed;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  background-image: url('~@/assets/img/background.png');
  background-size: cover;
  background-attachment: fixed;
  z-index: -1; /* 确保背景层在内容层之下 */
}

.form {
  position: absolute;
  transform: translate(-50%, 0%);
  padding:2%;
  top: 6%;
  left:50%;
  width: 45%;
  min-height: 500px;
  background: rgba(255, 255, 255, 0.2);
  backdrop-filter: blur(10px);
  border-radius: 20px; /* 设置圆角为20像素 */
  /* 其他样式，例如边框、阴影等 */
  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1); /* 添加轻微的阴影效果 */
}

.title {
  color: #fefefe;
  font-size: 4em; /* 设置字号大小 */
  margin:0%;
  font-family: 'STKaiti', 'KaiTi', sans-serif; /* 优先使用华文楷体，如果不可用则使用无衬线字体 */
  max-width: 80%;
  margin-top: 0vh; 
  text-align: center;
  margin-left: auto; /* 左外边距自动 */
  margin-right: auto; /* 右外边距自动 */
  margin-bottom: 0.5em;
}

button {
  justify-content: space-between;
  margin: auto;
  font-size: 1em;
  border: 1px solid #000; /* 边框样式，可以根据需要调整 */
  cursor: pointer; /* 鼠标悬停时显示指针手势 */
  border-radius: 8px; /* 添加圆角 */
}

button:hover {
  background-color: #56cfcf;
}

.return_button {
  transform: translate(-50%, -50%);
  font-size: 1.5em;
  position: absolute;
  top: 2em;
  left: 10%;
}

.submit_button {
  text-align: center;
  font-size: 1.5em;
  margin-top: 0.5em;
  margin-left: auto; /* 左外边距自动 */
  margin-right: auto; /* 右外边距自动 */
  display: block;
}

form > div {
  margin-bottom: 15px;
}

label {
  display: block;
  margin-bottom: 5px;
  color: #fefefe;
  font-size: 2em; /* 设置字号大小 */
  font-family: 'STKaiti', 'KaiTi', sans-serif; /* 优先使用华文楷体，如果不可用则使用无衬线字体 */
}

input[type="text"],
textarea {
  width: 100%;
  font-size: 1.5em;
  margin-top: 0.5em;
  margin-left: auto; /* 左外边距自动 */
  margin-right: auto; /* 右外边距自动 */
  display: block;
  border: 1px solid #ddd;
  border-radius: 4px;
}

input[type="text"] {
  min-height: 2em;
}

textarea {
  resize: none;
  height: 8em;
}


</style>