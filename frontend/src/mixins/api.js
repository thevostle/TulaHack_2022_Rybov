export default {
  data() {
    return {
      apiUrl: 'https://92f6-94-28-235-94.eu.ngrok.io/',
    };
  },
  methods: {
    async apiPost(action, data) {
      const payload = new URLSearchParams();

      for (const prop in data) {
        payload.append(prop, data[prop]);
      }

      const options = {
        method: 'POST',
        mode: 'cors',
        headers: {
          'Content-Type': 'application/x-www-form-urlencoded',
          'Access-Control-Allow-Origin': '*',
          'Access-Control-Allow-Headers': '*',
          'Access-Control-Request-Private-Network': false,
          credentials: 'include',
        },
        body: payload,
      };

      try {
        const response = await fetch(`${this.apiUrl}${action}`, options);

        if (response.ok) {
          const data = await response.json();
          return data;
        }
      } catch (error) {
        return error;
      }
    },
    async apiGet(action, data) {
      const payload = new URLSearchParams();

      for (const prop in data) {
        payload.append(prop, data[prop]);
      }

      const options = {
        method: 'GET',
        mode: 'cors',
        headers: {
          'Access-Control-Allow-Origin': '*',
          'Access-Control-Allow-Headers': '*',
          'Access-Control-Request-Private-Network': false,
          credentials: 'include',
        },
      };

      try {
        const response = await fetch(`${this.apiUrl}${action}?${payload}`, options);

        if (response.ok) {
          const data = await response.json();
          return data;
        }
      } catch (error) {
        return error;
      }
    },
  },
};