#include "ShopInfoPanel.h"
#include "Game.h"


ShopInfoPanel::ShopInfoPanel(Game* game, int xPos, int yPos) : PanelUI(game)
{
	//----MARCO----//

	_frame = new AnimatedImageUI(game, game->getTexture("InfoPanel"), xPos, yPos);

	//Animaciones
	_frame->addAnim(AnimatedImageUI::Default, 1, false);
	_frame->addAnim(AnimatedImageUI::Start, 6, false);
	_frame->addAnim(AnimatedImageUI::End, 6, false);

	_frame->playAnim(AnimatedImageUI::Default);

	addChild(_frame);

	//----INFORMACION----//

		// Nombre
	_nameText = new TextUI(game, "ExampleName", game->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	_nameText->setPosition((xPos + getInfoPanelWidth() / 2) - _nameText->getW() / 2, yPos + margin);
	addChild(_nameText);

		// Propiedades
	int size = 12, offsetY = 5;

	//--Damage
	_damageIcon = new ImageUI(game, game->getTexture("PowerIcon"));
	_damageIcon->setPosition(_frame->getX() + 7, _frame->getY() + 30);
	_damageIcon->setSize(size, size);

	_damageBar = new ImageUI(game, game->getTexture("PropertiesBar"));
	_damageBar->setPosition(_damageIcon->getX() + _damageIcon->getW() + 5, 
							_damageIcon->getY() + _damageIcon->getH() / 2 - _damageBar->getH() / 2);

	//--Cadence
	_cadenceIcon = new ImageUI(game, game->getTexture("CadenceIcon"));
	_cadenceIcon->setPosition(_damageIcon->getX(),
								_damageIcon->getY() + _damageIcon->getH() + offsetY);
	_cadenceIcon->setSize(size, size);

	_cadenceBar = new ImageUI(game, game->getTexture("PropertiesBar"));
	_cadenceBar->setPosition(_damageBar->getX(),
								_cadenceIcon->getY() + _cadenceIcon->getH() / 2 - _cadenceBar->getH() / 2);

	//--Clip
	_clipIcon = new ImageUI(game, game->getTexture("ClipIcon"));
	_clipIcon->setPosition(_cadenceIcon->getX(),
								_cadenceIcon->getY() + _cadenceIcon->getH() + offsetY);
	_clipIcon->setSize(size, size);

	_clipBar = new ImageUI(game, game->getTexture("PropertiesBar"));
	_clipBar->setPosition(_cadenceBar->getX(),
								_clipIcon->getY() + _clipIcon->getH() / 2 - _clipBar->getH() / 2);

	//--Precio
	_priceText = new TextUI(game, "0000", game->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	_priceIcon = new ImageUI(game, game->getTexture("CoinIcon"));

	_priceText->setPosition(_frame->getX() + getInfoPanelWidth() / 2 - (_priceText->getW() + _priceIcon->getW()) / 2,
							_clipBar->getY() + _clipBar->getH() + 8);
	_priceIcon->setPosition(_priceText->getX() + _priceText->getW(),
							_priceText->getY() + _priceText->getH() / 2 - _priceIcon->getH() / 2);

	setChildrenVisibility(false);

	addChild(_damageIcon);
	addChild(_damageBar);
	addChild(_cadenceIcon);
	addChild(_cadenceBar);
	addChild(_clipIcon);
	addChild(_clipBar);
	addChild(_priceText);
	addChild(_priceIcon);
}

void ShopInfoPanel::update(double deltaTime)
{
	PanelUI::update(deltaTime);

	if (_frame->getCurrentAnim() == AnimatedImageUI::End)
	{
		setChildrenVisibility(false);

		if (_frame->animationFinished())
			setVisible(false);
	}
	else if (_frame->getCurrentAnim() == AnimatedImageUI::Start)
	{
		_frame->setVisible(true);

		if (_frame->animationFinished())
		{
			_frame->playAnim(AnimatedImageUI::Default);

			setChildrenVisibility(true);
		}
		else
			setChildrenVisibility(false);
	}
}

void ShopInfoPanel::setChildrenVisibility(bool b)
{
	_nameText->setVisible(b);
	_damageIcon->setVisible(b);
	_damageBar->setVisible(b);
	_cadenceIcon->setVisible(b);
	_cadenceBar->setVisible(b);
	_clipIcon->setVisible(b);
	_clipBar->setVisible(b);
	_priceIcon->setVisible(b);
	_priceText->setVisible(b);
}

void ShopInfoPanel::openInfoPanel()
{
	setVisible(true);
	_frame->playAnim(AnimatedImageUI::Start);
	_game->getSoundManager()->playSFX("openDialogue");
}

void ShopInfoPanel::closeInfoPanel()
{
	_frame->playAnim(AnimatedImageUI::End);
	_game->getSoundManager()->playSFX("closeDialogue");
}

void ShopInfoPanel::setName(string name)
{
	_nameText->setText(name);
	_nameText->setPosition((int)((_frame->getX() + getInfoPanelWidth() / 2) - _nameText->getW() / 2), (int) (_frame->getY() + margin));
}

void ShopInfoPanel::setDamage(int damage)
{
	float widthRatio = ((float(_damageBar->getW()) * damage) / float(maxDamage)) / float(_damageBar->getW());
	_damageBar->setClippingAreaSize(widthRatio, 1);
	_damageBar->setSize(_damageBar->getClipArea().w, _damageBar->getClipArea().h);
}

void ShopInfoPanel::setClip(int clip)
{
	float widthRatio = ((float(_clipBar->getW()) * clip) / float(maxClip)) / float(_clipBar->getW());
	_clipBar->setClippingAreaSize(widthRatio, 1);
	_clipBar->setSize(_clipBar->getClipArea().w, _clipBar->getClipArea().h);
}

void ShopInfoPanel::setCadence(int cadence)
{
	float widthRatio = ((float(_cadenceBar->getW()) * cadence) / float(maxCadence)) / float(_cadenceBar->getW());
	_cadenceBar->setClippingAreaSize(widthRatio, 1);
	_cadenceBar->setSize(_cadenceBar->getClipArea().w, _cadenceBar->getClipArea().h);
}

void ShopInfoPanel::setPrice(int price)
{
	_priceText->setText(to_string(price));
}
