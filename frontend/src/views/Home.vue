<script setup>
import Aside from '../components/layout/Aside.vue';
import Browser from '../components/layout/Browser.vue';
</script>

<template>
  <div>
    <Aside />
    <Browser />
  </div>
</template>

<script>
export default {
  components: {
    Aside,
    Browser,
  },
};
</script>
