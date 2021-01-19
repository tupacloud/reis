app.component('dashboard-display', {
    data() {
        return {
            minimize: null        
        }
    },
    props: {
        view: {
            type: String,
            required: true
        },
        windows: {
            type: Array,
            required: true
        },
        isMovingWindow: {
            type: Boolean,
            required: true
        }
    },
    template:
    /*html*/
    `
    <dynamic-window 
        :title="window.title" 
        v-for="(window, key) in windows"  
        @minimize="minimizeWindow">

        <div v-if="window.type == 'history'"><history-display :id="key" :type="window.scale"></history-display></div>
        <div v-else-if="window.type == 'main'"><main-display></main-display></div>
        <div v-else-if="window.type == 'settings'"><settings-display @change-wallpaper="changeWallpaper" :cat="window.cat"></settings-display></div>

    </dynamic-window>   
    `,
    methods: {
        changeWallpaper(payload) {
            this.$emit('change-wallpaper', payload)
        },
        minimizeWindow(info) {
            this.$emit('minimize', info)
        }
    }
})