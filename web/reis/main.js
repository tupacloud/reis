const app = Vue.createApp({
    data() {
        return {
            user: 'Renato',
            menu_left: 20,
            menu_top: 60,
            menu_w: 0,
            menu_h: 0,
            tasks: [],
            windows: [
                {
                  "title": "Bem-vindo",
                  "type": "main"                
                }
              ],
            nivel: '90%',
            isMovingMenu: false,
            backImg: "./assets/images/wpp/3.jpg"
        }
    },
    methods: {
        changeWallpaper(payload) {
            console.log(payload)
            this.backImg = payload
        },
        minimizeWindow(info) {
            this.tasks.push(info)
        },
        openWindow(window) {
            this.windows.push(window)
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
        }
        
    },
    computed: {
        imageUrl: function() {
            return 'url('+ this.backImg + ')';
        }
   }
})