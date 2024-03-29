import {Component, OnInit, ViewChild} from '@angular/core';
import {NgForm} from "@angular/forms";
import {LoginService} from "./login.service";
import {Router} from "@angular/router";

@Component({
    selector: 'app-login',
    templateUrl: './login.page.html',
    styleUrls: ['./login.page.scss'],
})
export class LoginPage implements OnInit {

    @ViewChild('loginForm') public loginForm: NgForm;
    userNameMsg = '';
    passwordMsg = '';
    member = this.getMember();
    logged = true;

    constructor(private loginService: LoginService, private router: Router) {
    }

    ngOnInit() {

    }

    ionViewWillEnter() {
        this.userNameMsg = '';
        this.passwordMsg = '';
        this.logged = true;
        this.member = this.getMember();
        this.loginForm.resetForm()
    }

    onSubmit() {
        // this.loginService.accLogin(this.member).subscribe((result) => {
        //     let member: LoginDto = result;
        //     if (member != null) {
        //         if (member.reply === 'Success') {
        //             localStorage.setItem('member', JSON.stringify(member));
        //             this.router.navigate(['/main/home']);
        //         } else if (member.reply === 'Password Failed') {
        //             this.userNameMsg = '';
        //             this.passwordMsg = 'Password Failed';
        //             this.logged = false;
        //         } else if (member.reply === 'User cannot be found') {
        //             this.userNameMsg = 'User cannot be found';
        //             this.passwordMsg = '';
        //             this.logged = false;
        //         }
        //     } else {
        //         this.logged = false;
        //     }
        // });
        this.router.navigate(['/main']);
    }

    getMember() {
        return {
            nic: '',
            title: '',
            name: '',
            address: '',
            password: '',
            mobile: '',
            reply: ''
        }
    }
}
