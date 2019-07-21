public class GermanToUKPlugConnectorAdapter implements UKPlugConnector {

    private GermanPlugConnector plug;

    public GermanToUKPlugConnectorAdapter(GermanPlugConnector plug) {
        this.plug = plug;
    }

    @Override
    public void provideElectricity() {
        plug.giveElectricity();
    }

}
