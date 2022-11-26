<template>
  <transition name="v-popup-transition">
    <div class="v-popup">
      <div class="v-popup__shadow" @click="close" />
      <div class="v-popup__content">
        <div class="v-popup__closeButton" @click="close">х</div>
        <slot></slot>
      </div>
    </div>
  </transition>
</template>

<script>
export default {
  props: {
    popupName: {
      type: String,
      default: 'default',
    },
  },
  methods: {
    close: function () {
      this.$emit('close')
    },
  },
}
</script>

<style scoped>
.v-popup {
  position: fixed;
  top: 0;
  right: 0;
  bottom: 0;
  left: 0;
  z-index: 100000;
  overflow-x: hidden;
  overflow-y: auto;
  display: flex;
  align-items: center;
}
.v-popup__shadow {
  display: flex;
  position: fixed;
  top: 0;
  right: 0;
  bottom: 0;
  left: 0;
  z-index: 1;
  background-color: rgba(0, 0, 0, 0.4);
}
.v-popup__content {
  position: relative;
  background-color: #ffffff;
  border-radius: 5px;
  margin: auto;
  display: flex;
  flex-direction: column;
  z-index: 10;
  height: min-content;
}
.v-popup__closeButton {
  position: absolute;
  margin: 0 auto;
  right: 2rem;
  top: 2rem;
  z-index: 200000;
  cursor: pointer;

}
</style>