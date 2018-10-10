import { Component,OnInit} from '@angular/core';
import {BaseComponent} from "../../../../app/BaseComponent";
import {IdKycPersonComponent} from "../../../../pages/id/kyc/person/person";
import {IdKycCompanyComponent} from "../../../../pages/id/kyc/company/company";
import {KycOrderPage} from "../../../../pages/id/kyc/kyc-order/kyc-order";

import {PathlistPage} from '../../../../pages/id/pathlist/pathlist';
import {Config} from '../../../../providers/Config';

@Component({
  selector: 'page-kyc-operation',
  templateUrl: 'kyc-operation.html',
})
export class KycOperationPage  extends BaseComponent implements OnInit{
    private params;
    private aprType;
    private orderList;
    ngOnInit(){
      this.params  = this.getNavParams().data;
      this.aprType = this.params["type"];
      this.setTitleByAssets('text-id-kyc-operation');

      this.localStorage.getKyc().then((val)=>{
        let masterWalletId = Config.getCurMasterWalletId();

        this.orderList= JSON.parse(val)[masterWalletId][this.params["id"]]["kyc"][this.aprType]["order"];
      });
    }

    onNext(type) {
      if (type === 1) {
          this.add();
      } else if(type === 2) {
          if(this.isNull(this.orderList)){
               this.messageBox("text-id-kyc-no-order");
               return;
          }
          this.check();
      }else if(type === 3){
            this.Go(PathlistPage,this.params);
      }
    }

    add(){
      if(this.aprType === "person"){
         this.Go(IdKycPersonComponent,this.params);
      }else{
        this.Go(IdKycCompanyComponent,this.params);
      }
    }

    check(){
       this.Go(KycOrderPage,this.params);
    }
}
