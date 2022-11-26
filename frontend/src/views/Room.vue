<script setup>
import Aside from '../components/layout/Aside.vue';
</script>

<template>
  <div>
    <Aside />
    Комната №{{ roomId }}
  </div>
</template>

<script>
export default {
  components: {
    Aside,
  },
  data() {
    return {
      roomId: this.$route.params.roomId,
    };
  },
};
</script>
