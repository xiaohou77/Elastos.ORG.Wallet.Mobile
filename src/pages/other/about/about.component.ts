import { Component, OnInit } from '@angular/core';
import {BaseComponent} from '../../../app/BaseComponent';

@Component({
  selector: 'app-about',
  templateUrl: './about.component.html',
  styleUrls: ['./about.component.less']
})
export class AboutComponent extends BaseComponent implements OnInit {


  ngOnInit() {
  }

}
