const app = Vue.createApp({
    data() {
        return {
            user: 'Renato',
            menu_left: window.innerWidth - 330,
            menu_top: 150,
            menu_w: 0,
            menu_h: 0,
            nivel: '90%',
            isMovingMenu: false,
            dash_view: 'main'
        }
    },
    methods: {
        changeView(option) {
            this.dash_view = option
        },
        mouseMoveHandler(event) {
            if (this.isMovingMenu) {
                if (event.clientX < window.innerWidth - 115 && event.clientX > 100 ) {
                    this.menu_left = event.clientX - this.menu_w/2;
                    this.menu_top = event.clientY - this.menu_h/2;
                }
            }
        },
        mouseUpHandler() {
            if (this.isMovingMenu) {
                this.isMovingMenu = false;  
            }
        },
        moveElement(info) {
            this.isMovingMenu = true;
            this.menu_w = info.object.clientWidth;
            this.menu_h = info.object.clientHeight;
        },
    },
    computed: {
        
    }
})