<script setup>
import { RouterLink, RouterView } from 'vue-router';
import 'material-design-icons-iconfont/dist/material-design-icons.css';

import api from './mixins/api.js';
</script>

<template>
  <v-app
    id="inspire"
    theme="dark">
    <v-main><RouterView /></v-main>
  </v-app>
</template>

<script>
export default {
  mixins: [api],
};
</script>

<style scoped>
.inputNewUser {
  border: thin solid currentColor;
}

header {
  line-height: 1.5;
  max-height: 100vh;
}

.logo {
  display: block;
  margin: 0 auto 2rem;
}

nav {
  width: 100%;
  font-size: 12px;
  text-align: center;
  margin-top: 2rem;
}

a {
  text-decoration: none;
}

.navLink {
  color: #ebebeba3;
  width: 100%;
}

nav a.router-link-exact-active {
  color: var(--color-text);
}

nav a.router-link-exact-active:hover {
  background-color: transparent;
}

nav a {
  display: inline-block;
  padding: 0 1rem;
  border-left: 1px solid var(--color-border);
}

nav a:first-of-type {
  border: 0;
}

@media (min-width: 1024px) {
  header {
    display: flex;
    place-items: center;
    padding-right: calc(var(--section-gap) / 2);
  }

  .logo {
    margin: 0 2rem 0 0;
  }

  header .wrapper {
    display: flex;
    place-items: flex-start;
    flex-wrap: wrap;
  }

  nav {
    text-align: left;
    margin-left: -1rem;
    font-size: 1rem;

    padding: 1rem 0;
    margin-top: 1rem;
  }
}

.wrapper {
  justify-content: center;
  width: 90%;
  align-self: center;
}
</style>
