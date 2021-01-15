const app = Vue.createApp({
    data() {
        return {
            user: 'Renato',
            menu_left: 20,
            menu_top: 0,
            nivel: '90%',
            isMovingMenu: false
        }
    },
    methods: {
        mouseMoveHandler(event) {
            if (this.isMovingMenu) {
                if (event.clientX < window.innerWidth - 115 && event.clientX > 100 ) {
                    this.menu_left = event.screenX - 95;
                    this.menu_top = event.screenY - 95;
                }
            }
        },
        mouseUpHandler() {
            if (this.isMovingMenu) {
                this.isMovingMenu = false;  
            }
        },
        moveElement(event) {
            this.isMovingMenu = true;
            console.log(event.clientX);
        },
    }
})