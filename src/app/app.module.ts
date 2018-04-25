import {NgModule} from '@angular/core';
import {CommonModule} from '@angular/common';

import {AppRoutingModule} from './app-routing.module';
import {BrowserModule} from '@angular/platform-browser';
import {HttpClientModule, HttpClient} from '@angular/common/http';
import {WeUiModule} from 'ngx-weui';
import {TranslateLoader, TranslateModule, TranslateService} from '@ngx-translate/core';
import {TranslateHttpLoader} from '@ngx-translate/http-loader';
import {QRCodeModule} from 'angular2-qrcode';
import {FormsModule} from '@angular/forms';


/**provider*/
import {LoDashStatic as _} from 'lodash';
import {RouterUtil} from './../providers/RouterUtil';
import {Config} from './../providers/Config';
import {LocalStorage} from './../providers/Localstorage';

/**pages*/
import {AppComponent} from './app.component';
import {HeaderComponent} from './header/app.header';
import {TabsComponent} from './../pages/tabs/tabs.component';
import {HomeComponent} from './../pages/tabs/home/home.component';
import {MyComponent} from './../pages/tabs/my/my.component';
import {LauncherComponent} from '../pages/launcher/launcher.component';
import {ManagerComponent} from '../pages/wallet/manager/manager.component';
import {ImportComponent} from '../pages/wallet/import/import.component';
import {ExprotPrikeyComponent} from '../pages/wallet/exprot-prikey/exprot-prikey.component';
import {MnemonicComponent} from '../pages/mnemonic/mnemonic.component';
import {WriteComponent} from '../pages/mnemonic/write/write.component';
import {AddressComponent} from '../pages/wallet/address/address.component';
import {MultiSignedComponent} from '../pages/multi-signed/multi-signed.component';
import {JoinComponent} from '../pages/multi-signed/join/join.component';
import {ContactsComponent} from '../pages/contacts/contacts.component';
import {SettingsComponent} from '../pages/universal/settings/settings.component';
import {ResultComponent} from '../pages/universal/result/result.component';
import {CoinComponent} from '../pages/coin/coin.component';
import {RecordComponent} from '../pages/coin/record/record.component';
import {TransferComponent} from '../pages/coin/transfer/transfer.component';
import {ReceiveComponent} from '../pages/coin/receive/receive.component';
import {ContactListComponent} from '../pages/contacts/contact-list/contact-list.component';
import {ContactCreateComponent} from '../pages/contacts/contact-create/contact-create.component';
import {CoinListComponent} from '../pages/coin/coin-list/coin-list.component';
import {WalletCreateComponent} from '../pages/wallet/wallet-create/wallet-create.component';
import {WalletInfoComponent} from '../pages/wallet/wallet-info/wallet-info.component';
import {Native} from '../providers/Native';
import {Logger} from '../providers/Logger';
import {Validators} from '../providers/Validators';
import {BaseComponent} from './BaseComponent';
import { RecordinfoComponent } from '../pages/coin/recordinfo/recordinfo.component';
import {Utils} from '../providers/Utils';
import { AboutComponent } from '../pages/other/about/about.component';
import { HelpComponent } from '../pages/other/help/help.component';
import { NoticeComponent } from '../pages/other/notice/notice.component';
import { ChangePwdComponent } from '../pages/other/change-pwd/change-pwd.component';
import { ChangeNameComponent } from '../pages/other/change-name/change-name.component';



export function HttpLoaderFactory(http: HttpClient) {
  return new TranslateHttpLoader(http, './assets/i18n/', '.json');
}


@NgModule({
  declarations: [
    HeaderComponent,
    BaseComponent,
    AppComponent,
    TabsComponent,
    HomeComponent,
    MyComponent,
    LauncherComponent,
    ManagerComponent,
    ImportComponent,
    ExprotPrikeyComponent,
    MnemonicComponent,
    WriteComponent,
    AddressComponent,
    MultiSignedComponent,
    JoinComponent,
    ContactsComponent,
    SettingsComponent,
    ResultComponent,
    CoinComponent,
    RecordComponent,
    TransferComponent,
    ReceiveComponent,
    ContactListComponent,
    ContactCreateComponent,
    CoinListComponent,
    WalletCreateComponent,
    WalletInfoComponent,
    RecordinfoComponent,
    AboutComponent,
    HelpComponent,
    NoticeComponent,
    ChangePwdComponent,
    ChangeNameComponent
  ],
  imports: [
    AppRoutingModule,
    BrowserModule,
    HttpClientModule,
    WeUiModule.forRoot(),
    FormsModule,
    TranslateModule.forRoot({
      loader: {
        provide: TranslateLoader,
        useFactory: (HttpLoaderFactory),
        deps: [HttpClient]
      }
    }),
    QRCodeModule
  ],
  providers: [
    HttpClientModule,
    HttpClient,
    RouterUtil,
    Config,
    LocalStorage,
    Native,
    Logger,
    Validators,
    HeaderComponent,
    Utils
  ],
  bootstrap: [AppComponent]
})
export class AppModule {
}
